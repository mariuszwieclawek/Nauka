/*-------------------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - laboratorium
					Lab 8 - Cwiczenie 2: pomiar przyspieszenia XYZ
					autor: Mariusz Sokolowski
					wersja: 28.09.2021r.
----------------------------------------------------------------------------*/

#include "frdm_bsp.h" 
#include "lcd1602.h"
#include "leds.h" 
#include "stdio.h"
#include "math.h"
#include "i2c.h"
#define	ZYXDR_Mask	1<<3	// Maska bitu ZYXDR w rejestrze STATUS

static uint8_t arrayXYZ[6];
static uint8_t sens;
static uint8_t status;
double X, Y, Z;

int main (void)
{ 
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	
	LED_Init();
	LCD1602_Init();	// Tu jest równiez inicjalizacja portu I2C0
	LCD1602_Backlight(TRUE);

	sens=0;	// Wybór czulosci: 0 - 2g; 1 - 4g; 2 - 8g
	I2C_WriteReg(0x1d, 0x2a, 0x0);	// ACTIVE=0 - stan czuwania
	I2C_WriteReg(0x1d, 0xe, sens);	 		// Ustaw czulosc zgodnie ze zmienna sens
	I2C_WriteReg(0x1d, 0x2a, 0x1);	 		// ACTIVE=1 - stan aktywny

	while(1)
	{
		I2C_ReadReg(0x1d, 0x0, &status);
		status&=ZYXDR_Mask;
		if(status)	// Czy dane gotowe do odczytu?
		{
			I2C_ReadRegBlock(0x1d, 0x1, 6, arrayXYZ);
			X=((double)((int16_t)((arrayXYZ[0]<<8)|arrayXYZ[1])>>2)/(4096>>sens));
			Y=((double)((int16_t)((arrayXYZ[2]<<8)|arrayXYZ[3])>>2)/(4096>>sens));
			Z=((double)((int16_t)((arrayXYZ[4]<<8)|arrayXYZ[5])>>2)/(4096>>sens));
			LCD1602_SetCursor(0,0);
			sprintf(display,"X:%+4.2f ",X);	// Przyspieszenie w osi X
			LCD1602_Print(display);
			sprintf(display,"Y:%+4.2f ",Y);	// Przyspieszenie w osi Y
			LCD1602_Print(display);
			LCD1602_SetCursor(0,1);
			sprintf(display,"Z:%+4.2f ",Z);	// Przyspieszenie w osi Z
			LCD1602_Print(display);
			
			if(fabs(X)>1.3)
				PTB->PSOR|=LED_R_MASK; // Wylacz czerwona diode LED
			else if(fabs(X)<1.1 && fabs(X)>0.9)
			{
				PTB->PCOR|=LED_R_MASK; // Wlacz czerwona diode LED
				PTB->PSOR|=(LED_G_MASK | LED_B_MASK); // Wylacz inne
			}

			if(fabs(Y)>1.3)
				PTB->PSOR|=LED_G_MASK; // Wylacz zielona diode LED
			else if(fabs(Y)<1.1 && fabs(Y)>0.9)
			{
				PTB->PCOR|=LED_G_MASK; // Wlacz zielona diode LED
				PTB->PSOR|=(LED_R_MASK | LED_B_MASK); // Wylacz inne
			}


			if(fabs(Z)>1.3)
				PTB->PSOR|=LED_B_MASK; // Wylacz niebeiska diode LED
			else if(fabs(Z)<1.1 && fabs(Z)>0.9)
			{
				PTB->PCOR|=LED_B_MASK;	// Wlacz niebieska diode LED
				PTB->PSOR|=(LED_G_MASK | LED_R_MASK); // Wylacz inne
			}
		}
	}
}

/*-------------------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - laboratorium
					Lab 8 - Cwiczenie 1: szukanie urzadzen na magistrali I2C
					autor: Mariusz Sokolowski
					wersja: 28.09.2021r.
----------------------------------------------------------------------------*/

#include "frdm_bsp.h" 
#include "stdio.h"
#include "i2c.h"
#include "lcd1602.h"

int main (void)
{ 
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	
	LCD1602_Init();	// Tu jest równiez inicjalizacja portu I2C0
	LCD1602_Backlight(TRUE);
	
	uint8_t error;
		
	for(uint8_t address=1; address<128; address++)
	{
		error=I2C_Ping(address);	
		if(error==0)	// Czy urzadzenie o adresie address istnieje?
		{
			sprintf(display, "0x%02X  ",address);	// Wyswietl adres urzadzenia w kodzie hex
			LCD1602_Print(display);
		}
	}

	while(1); 
}

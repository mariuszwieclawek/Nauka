/*-------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - laboratorium
					Lab 3 - Licznik SysTick
					autor: Mariusz Sokolowski
					wersja: 28.09.2021r.
----------------------------------------------------------------------------*/
	
#include "MKL05Z4.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include "leds.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
uint32_t czas=0;				// Licznik czasu, zliczajacy sekundy od handlera
uint8_t sekunda=0;			// Licznik przerwan ( do 10)
uint8_t sekunda_OK=0;		// "1"oznacza, ze handler od SysTick zliczyl 10 przerwan, kazde po 0.1s, czyli jedna sekunde

void SysTick_Handler(void)	// Podprogram obslugi przerwania od SysTick'a
{ 
	sekunda+=1;				// Licz interwaly równe 100ms
	if(sekunda==10)
	{
		sekunda=0;
		sekunda_OK=1;		// Daj znac, ze minela sekunda
	}
}


int main (void) 
{
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	
	LED_Init();									// Inicjalizacja diod LED
	LCD1602_Init();		 					// Inicjalizacja LCD
	LCD1602_Backlight(TRUE);  	// Wlaczenie podswietlenia
	LCD1602_ClearAll();					// Wyczysc ekran
	LCD1602_Print("    We are");		// Wyswietl powitanie (ciag tekstowy)
	LCD1602_SetCursor(0,1);			// Ustaw kursor na poczatku drugiej linii
	LCD1602_Print("  the robots");	// Wyswietl powitanie c.d.
	LCD1602_SetCursor(0,0);
	
	SysTick_Config(SystemCoreClock/10 );	// Start licznika SysTick ( przerwanie co 100ms)
	while(czas<5)		// Wyswietlaj ekran powitalny przez 5 sekund
	{
		if(sekunda_OK)
		{
			czas+=1;			// Licz sekundy
			sekunda_OK=0;
		}
	}
	czas=0;
	LCD1602_ClearAll();
	sprintf(display,"t=%02d",czas);	// Wyswietl stan poczatkowy licznika czasu
	LCD1602_Print(display);
	
  while(1)		// Poczatek petli glównej
	{
		if(sekunda_OK)
		{
			czas+=1;
			if(czas==100)		// Licz sekundy do 100 (odmierz 100 sekund)
				czas=0;
			LCD1602_SetCursor(2,0);
			sprintf(display,"%02d",czas);	// Wyswietl aktualny czas stopera
			LCD1602_Print(display);
			PTB->PTOR|=LED_R_MASK;	// Wlacz czerwona diode LED na czas 1s lub wylacz na czas 1s
			sekunda_OK=0;
		}
	}	
}

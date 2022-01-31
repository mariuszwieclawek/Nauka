/*---------------------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - laboratorium
					Lab 5 - Ćwiczenie 6: Sterowanie jasnością diody LED za pomocą przetwornika C/A
					autor: Mariusz Sokołowski
					wersja: 07.11.2020r.
-----------------------------------------------------------------------------------------*/
					
#include "MKL05Z4.h"
#include "ADC.h"
#include "DAC.h"
#include "tsi.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float volt_coeff = ((float)(((float)2.91) / 4095) );			// Współczynnik korekcji wyniku, w stosunku do napięcia referencyjnego przetwornika
uint8_t wynik_ok=0;
uint16_t temp, slider;
uint16_t dac;
float	wynik;

void ADC0_IRQHandler()
{	
	temp = ADC0->R[0];	// Odczyt danej i skasowanie flagi COCO
	if(!wynik_ok)				// Sprawdź, czy wynik skonsumowany przez petlę główną
	{
		wynik = temp;			// Wyślij nową daną do pętli głównej
		wynik_ok=1;
	}
	NVIC_ClearPendingIRQ(ADC0_IRQn);
}
int main (void)
{
	uint8_t	kal_error;
	slider=50;
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	TSI_Init();					// Inicjalizacja pola dotykowego - Slider
	LCD1602_Init();		 	// Inicjalizacja wyświetlacza LCD
	LCD1602_Backlight(TRUE);
	sprintf(display,"Slider=%02d",slider);
	LCD1602_SetCursor(0,0);
	LCD1602_Print(display);
	LCD1602_SetCursor(0,1);
	LCD1602_Print("Uk=");
	
	kal_error=ADC_Init();		// Inicjalizacja i kalibracja przetwornika A/C
	if(kal_error)
	{
		while(1);							// Klaibracja się nie powiodła
	}
	DAC_Init();		// Inicjalizacja prztwornika C/A
	dac=43*slider;	// Rozszerzenie zakresu pola dotykowego do 12 bitów
	DAC_Load_Trig(dac);	// Wyzwolenie prztwornika C/A wartością początkową
	ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(0);		// Pierwsze wyzwolenie przetwornika ADC0 w kanale 0 i odblokowanie przerwania
	
	while(1)
	{
		if(wynik_ok)
		{
			slider=TSI_ReadSlider();
			if(slider!=0)
			{
				sprintf(display,"%02d",slider);
				LCD1602_SetCursor(7,0);
				LCD1602_Print(display);
				slider-=2;		// Korekcja zakresu zmienności
				dac=43*slider;	// Rozszerzenie zakresu pola dotykowego do 12 bitów
				DAC_Load_Trig(dac);		// Ustawienie nowej wartości prztwornika C/A
			}
			wynik = wynik*volt_coeff;		// Dostosowanie wyniku do zakresu napięciowego
			sprintf(display,"%.3fV",wynik);
			LCD1602_SetCursor(3,1);
			LCD1602_Print(display);
			wynik_ok=0;
		}
	}
}

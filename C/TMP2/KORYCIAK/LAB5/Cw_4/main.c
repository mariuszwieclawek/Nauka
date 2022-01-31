/*--------------------------------------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - laboratorium
					Lab 5 - Ćwiczenie 4: wyzwalanie sprzętowe przetwornika A/C - tryb wyzwalania na żądanie (PIT0)
					autor: Mariusz Sokołowski
					wersja: 07.11.2020r.
---------------------------------------------------------------------------------------------------------*/
					
#include "MKL05Z4.h"
#include "ADC.h"
#include "pit.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float volt_coeff = ((float)(((float)2.91) / 4095) );			// Współczynnik korekcji wyniku, w stosunku do napięcia referencyjnego przetwornika
uint8_t wynik_ok=0;
uint16_t temp;
float	wynik;

void PIT_IRQHandler()
{
	PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;		// Skasuj flagę żądania przerwania
	NVIC_ClearPendingIRQ(PIT_IRQn);
}

void ADC0_IRQHandler()
{	
	temp = ADC0->R[0];		// Odczyt danej i skasowanie flagi COCO
	if(!wynik_ok)					// Sprawdź, czy wynik skonsumowany przez pętlę główną
	{
		wynik = temp;				// Wyślij nową daną do pętli głównej
		wynik_ok=1;
	}
	NVIC_ClearPendingIRQ(ADC0_IRQn);
}
int main (void)
{
	uint8_t	kal_error;
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	LCD1602_Init();		 // Inicjalizacja wyświetlacza LCD
	LCD1602_Backlight(TRUE);
	LCD1602_Print("---");		// Ekran kontrolny - nie zniknie, jeśli dalsza część programu nie działa
	PIT_Init();							// Inicjalizacja licznika PIT0
	
	kal_error=ADC_Init();		// Inicjalizacja i kalibracja przetwornika A/C
	if(kal_error)
	{
		while(1);							// Klaibracja się nie powiodła
	}
	
	ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(0);		// Odblokowanie przerwania i wybranie kanału nr 0
	
	while(1)
	{
		if(wynik_ok)
		{
			wynik = wynik*volt_coeff;		// Dostosowanie wyniku do zakresu napięciowego
			sprintf(display,"U=%.4fV",wynik);
			LCD1602_SetCursor(0,0);
			LCD1602_Print(display);
			wynik_ok=0;
		}
	}
}

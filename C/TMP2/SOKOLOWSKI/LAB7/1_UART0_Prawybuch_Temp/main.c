/*-------------------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - laboratorium
					Lab 7 - Ćwiczenie 1: nawiązywanie połączenia z komputerem za pomocą portu szeregowego UART0
					autor: Mariusz Sokołowski
					wersja: 28.09.2021r.
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "MKL05Z4.h"
#include "frdm_bsp.h"
#include "uart0.h"
#include "i2c.h"
#include "lcd1602.h"
#include "tsi.h"
#include "pit.h"
#include "ADC.h"


#define CR	0xd		// Powrót karetki

// zmienne globalne
float adc_volt_coeff = ((float)(((float)2.91) / 4095) );			// Wsp�czynnik korekcji wyniku, w stosunku do napi�cia referencyjnego przetwornika
uint8_t wynik_ok=0;
uint16_t temp;
float	wynik;


void ADC0_IRQHandler()
{	
	temp = ADC0->R[0];		// Odczyt danej i skasowanie flagi COCO
	if(!wynik_ok)					// Sprawd�, czy wynik skonsumowany przez petl� g��wn�
	{
		wynik = temp;				//  Wy�lij now� dan� do p�tli g��wnej
		wynik_ok=1;
	}
}

int main (void)
{
	uint32_t baud_rate, i=0;
	uint8_t w=0;
	uint8_t	kal_error;
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	LCD1602_Init();
	LCD1602_Backlight(TRUE);
	LCD1602_Print("Wybierz BR");
	UART0_Init();		// Inicjalizacja portu szeregowego UART0
	TSI_Init();
	
	while(w==0)
		w=TSI_ReadSlider();		// Ustaw BR dla UART0, dotyka�c pole: 0<1/3 - 9600, 1/3<2/3 - 28800,2/3< - 230400
	
	UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK );		//Blokada nadajnika i o dbiornika
	
	if(w<33)
	{
		UART0->BDH = 1;			//Dla CLOCK_SETUP=0 BR=9600
		UART0->BDL =17;			//Dla CLOCK_SETUP=0 BR=9600
		baud_rate=9600;
	}
	if((w>33)&&(w<66))
	{
		UART0->BDH = 0;			//Dla CLOCK_SETUP=0 BR=28800
		UART0->BDL =91;			//Dla CLOCK_SETUP=0 BR=28800
		baud_rate=28800;
	}
	if(w>66)
	{
		UART0->BDH = 0;			//Dla CLOCK_SETUP=0 BR=230400
		UART0->BDL =11;			//Dla CLOCK_SETUP=0 BR=230400
		baud_rate=230400;
	}	

	
	sprintf(display,"BR=%d b/s",baud_rate);	// Wy�wietlenie aktualnejj warto�ci BR
	LCD1602_SetCursor(0,0);
	LCD1602_Print(display);
	LCD1602_SetCursor(0,1);
	LCD1602_Print("Ustaw BR w PC...");
	DELAY(500)
	w=0;
	while(w==0)
		w=TSI_ReadSlider();		// Ustaw BR w komputerze i dotknij pole dotykowe
	
	LCD1602_SetCursor(0,1);
	LCD1602_Print("Transmisja...   ");
	UART0->C2 |= UART0_C2_TE_MASK;		//W��cz nadajnik
	
	
	kal_error=ADC_Init();		// Inicjalizacja i kalibracja przetwornika A/C
	if(kal_error)
	{
		while(1);							// Klaibracja si� nie powiod�a
	}
	
	ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(26);		// Pierwsze wyzwolenie przetwornika ADC0 w kanale 26 i odblokowanie przerwania

	while(1)
	{		
		if (wynik_ok == 1){
				wynik = wynik*adc_volt_coeff;		// Dostosowanie wyniku do zakresu napi�ciowego
				wynik=25-((wynik-0.716)/0.00162);
				sprintf(display,"T=%.1f%cC%c",wynik,0xF8,CR); //(char)223 ewentualnie zamiast 0xF8
				wynik_ok = 0;
		}
		for(i=0;display[i]!=0;i++){
				while(!(UART0->S1 & UART0_S1_TDRE_MASK));	// Czy nadajnik jest pusty?
				UART0->D = display[i];		// Wy�lij aktualn� warto�� licznika
		}
		DELAY(500)
	}
}

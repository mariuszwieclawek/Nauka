/*-------------------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - laboratorium
					Lab 7 - Ćwiczenie 1: odczyt flagi BF i adresu licznika LCD
					autor: Mariusz Sokołowski
					wersja: 23.11.2020r.
----------------------------------------------------------------------------*/
					
#include "MKL05Z4.h"
#include "lcd1602.h"
#include "frdm_bsp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint8_t temp;
double	wynik=1.1;
uint8_t bf_flag;

int main (void)
{
	//uint8_t temp;
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	
	
	LCD1602_Init();		 // Inicjalizacja LCD
	LCD1602_PL_CH();
	LCD1602_Backlight(TRUE);
	LCD1602_Print("---");	// Ekran kontrolny - nie zniknie, jeśli dalsza część programu nie działa
	while(1)
	{
			LCD1602_SetCursor(0,0);
			LCD1602_PrintPL("ko//n si//e u//smia//l");
			LCD1602_SetCursor(0,1);
			LCD1602_PrintPL("///z//o//l//c/");
			
	}
}

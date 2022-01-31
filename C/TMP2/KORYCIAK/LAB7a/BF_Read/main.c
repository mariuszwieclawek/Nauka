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
uint8_t counter=0;
uint8_t cursor=0;
uint8_t row0=0;
uint8_t row1=1;
double	wynik=1.1;
uint8_t bf_flag;

int main (void)
{
	//uint8_t temp;
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	
	
	LCD1602_Init();		 // Inicjalizacja LCD
	LCD1602_Backlight(TRUE);
	LCD1602_Blink_Off_Cursor_On();
	while(1)
	{
			LCD1602_SetCursor(cursor,row0);
			bf_flag = LCD1602_BF_AC(&temp);
			sprintf(display,"%03d",temp);
			LCD1602_SetCursor(13,row1);
			LCD1602_Print(display);
			LCD1602_SetCursor(cursor,row0);
			DELAY(500)
			counter+=1;
			cursor+=1;
			if(counter==40)
			{
				cursor=0x0;
				LCD1602_SetCursor(13,row1);
				LCD1602_Print("   ");
				row0=1;
				row1=0;
			}
			if(counter==80)
			{
				cursor=0x0;
				LCD1602_SetCursor(13,row1);
				LCD1602_Print("   ");
				row0=0;
				row1=1;
				counter=0;
			}
	}
}

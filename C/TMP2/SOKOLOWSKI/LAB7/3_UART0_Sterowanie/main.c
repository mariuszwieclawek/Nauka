/*-------------------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - laboratorium
					Lab 7 - Ćwiczenie 3: sterowanie urządzeniami zewnętrznymi przez komputer
					autor: Mariusz Sokołowski
					wersja: 28.09.2021r.
----------------------------------------------------------------------------*/
					
#include "MKL05Z4.h"
#include "uart0.h"
#include "led.h"
#include "lcd1602.h"
#include "i2c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LF	0xa		// Enter
#define CR	0x21		// Powrtót karetki

char rx_buf[16];
char LED_R_ON[]="LRON";
char LED_R_OFF[]="LROFF";
char LED_G_ON[]="LGON";
char LED_G_OFF[]="LGOFF";
char LED_B_ON[]="LBON";
char LED_B_OFF[]="LBOFF";
char Error[]="Zla komenda";
char Too_Long[]="Zbyt dlugi ciag";
uint8_t rx_buf_pos=0;
char temp,buf;
uint8_t rx_FULL=0;
uint8_t too_long=0;

char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}; //buffer

void UART0_IRQHandler()
{
	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{
		temp=UART0->D;	// Odczyt wartości z bufora odbiornika i skasowanie flagi RDRF
		if(!rx_FULL)
		{
			if(temp!=CR)
			{
				rx_buf[rx_buf_pos] = temp;	// Kompletuj komendę
				rx_buf_pos++;
			}
			else
			{
				rx_buf[rx_buf_pos] = 0;
				rx_FULL=1;
			}
		}
	NVIC_EnableIRQ(UART0_IRQn);
	}
	
	/*
	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{
		temp=UART0->D;	// Odczyt wartości z bufora odbiornika i skasowanie flagi RDRF
		if(!rx_FULL)
		{
			if(temp!=CR)
			{
				//if(!too_long)	// Jeśli za długi ciąg, ignoruj resztę znaków
				//{
					rx_buf[rx_buf_pos] = temp;	// Kompletuj komendę
					rx_buf_pos++;
					if(rx_buf_pos==16)
						too_long=1;		// Za długi ciąg
				//}
			}
			else
			{
				//if(!too_long)	// Jeśli za długi ciąg, porzuć tablicę
					rx_buf[rx_buf_pos] = 0;
				rx_FULL=1;
			}
		}
		

	NVIC_EnableIRQ(UART0_IRQn);
	}*/
}

int main (void)
{	
	uint8_t i;
	LED_Init();
	UART0_Init();		// Inicjalizacja portu szeregowego UART0
	LCD1602_Init();
	LCD1602_Backlight(TRUE);
	LCD1602_ClearAll();
	
	while(1)
	{

		if(rx_FULL)		// Czy dana gotowa?
		{
			sprintf(display,"TURN ON MODULE"); 
			for(int i=0;rx_buf[i]!=0;i++)
			{
				while(!(UART0->S1 & UART0_S1_TDRE_MASK));	// Is the transmitter empty?
				UART0->D = rx_buf[i];		// send to user
			}
			if(too_long)
			{
				for(i=0;Too_Long[i]!=0;i++)	// Zbyt długi ciąg
					{
						while(!(UART0->S1 & UART0_S1_TDRE_MASK));	// Czy nadajnik gotowy?
						UART0->D = Too_Long[i];
					}
					while(!(UART0->S1 & UART0_S1_TDRE_MASK));	// Czy nadajnik gotowy?
					UART0->D = LF;		// Następna linia
					while(!(UART0->S1 & UART0_S1_TDRE_MASK));	// Czy nadajnik gotowy?
					UART0->D = CR;		// Początek linii
					too_long=0;
			}
			else
			{
				if(strcmp (rx_buf,LED_R_ON)==0)	// Zaświeć czerwoną diodę LED 
					PTB->PCOR = (1<<8);
				else if(strcmp (rx_buf,LED_R_OFF)==0) // Zgaś czerwoną diodę LED
						PTB->PSOR = (1<<8);					
				else if(strcmp (rx_buf,LED_G_ON)==0)	// Zaświeć zieloną diodę LED 
					PTB->PCOR = (1<<9);
				else if(strcmp (rx_buf,LED_G_OFF)==0) // Zgaś zieloną diodę LED
						PTB->PSOR = (1<<9);					
				else if(strcmp (rx_buf,LED_B_ON)==0)	// Zaświeć niebieską diodę LED 
					PTB->PCOR = (1<<10);
				else if(strcmp (rx_buf,LED_B_OFF)==0) // Zgaś niebieską diodę LED
						PTB->PSOR = (1<<10);					
				else
					{
						for(i=0;Error[i]!=0;i++)	// Zła komenda
						{
							while(!(UART0->S1 & UART0_S1_TDRE_MASK));	// Czy nadajnik gotowy?
							UART0->D = Error[i];
						}
						while(!(UART0->S1 & UART0_S1_TDRE_MASK));	// Czy nadajnik gotowy?
						UART0->D = LF;		// Następna linia
						while(!(UART0->S1 & UART0_S1_TDRE_MASK));	// Czy nadajnik gotowy?
						UART0->D = CR;		// Początek linii
					}
				}
				
			rx_buf_pos=0;
			rx_FULL=0;	// Dana skonsumowana
		}
	}
}

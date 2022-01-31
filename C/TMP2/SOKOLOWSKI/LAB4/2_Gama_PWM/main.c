/*-------------------------------------------------------------------------
					Technika Mikroprocesorowa 2 - laboratorium
					Lab 4 - TPM/PWM - generator dźwięków temperowanych (8 oktaw)
					autor: Mariusz Sokolowski
					wersja: 28.09.2021r.
----------------------------------------------------------------------------*/
	
#include "MKL05Z4.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include "klaw.h"
#include "TPM.h"
#include "tsi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void) 
{
	LCD1602_Init();		 // Inicjalizacja LCD
	LCD1602_Backlight(TRUE);
	PWM_Init();				// Inicjalizacja licznika TPM0 (PWM „Low-true pulses”)

	LCD1602_ClearAll();
	
	uint16_t	mod_curr;
	uint16_t	ampl;
	int gora_dol = 1;
	int dzielnik =16;
	int freq = 200000;
	
  while(1)
	{
		if(gora_dol)
		{
			mod_curr=freq/dzielnik;
			TPM0->MOD = mod_curr;
			dzielnik+=1;
			if(dzielnik==128)
				gora_dol = 0;
			TPM0->CONTROLS[2].CnV = mod_curr*0.5;	// Nowa wartość kreująca współczynnik wypełnienia PWM
		}
		else if(gora_dol == 0)
		{
			mod_curr=freq/dzielnik;
			TPM0->MOD = mod_curr;
			dzielnik-=1;
			if(dzielnik==16)
				gora_dol = 1;
			TPM0->CONTROLS[2].CnV = mod_curr*0.5;	// Nowa wartość kreująca współczynnik wypełnienia PWM
		}
		DELAY(20)
	}
}

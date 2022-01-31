/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file tpm.c
 * @author Koryciak
 * @date Nov 2020
 * @brief File containing definitions for TPM.
 * @ver 0.1
 */

#include "tpm.h"

/******************************************************************************\
* Private definitions
\******************************************************************************/
/******************************************************************************\
* Private prototypes
\******************************************************************************/
void TPM1_IRQHandler(void);
/******************************************************************************\
* Private memory declarations
\******************************************************************************/
static uint16_t tpm1Diff = 0;
static uint16_t tpm1New = 0;
static uint16_t tpm1Old = 0;
static uint8_t tpm0Enabled = 0;

void TPM1_Init_InputCapture(void) {
		
//  SIM->SCGC6 |= SIM_SCGC6_XXX_MASK;		// ToDo 2.1.1: Enable TPM1 mask in SCGC6 register
//	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(XXX);// ToDo 2.1.1: Choose MCGFLLCLK clock source
	
//	SIM->SCGC5 |= SIM_SCGC5_PORTX_MASK; // ToDo 2.1.2: Connect port A to clock
//	PORTA->PCR[XXX] = PORT_PCR_MUX(X);  // ToDo 2.1.2: Set multiplekser to TPM1 for PTA0, get channel number (page 148 of the Reference Manual)
	
//	TPM1->SC |= TPM_SC_PS(XXX);  				// ToDo 2.1.3: Set prescaler to 128
//	TPM1->SC |= TPM_SC_CMOD(X);					// ToDo 2.1.4: For TMP1, select the internal input clock source
	
// ToDo 2.1.5: Connect correct channel from TPM1 for "input capture" mode
//	TPM1->SC &= ~TPM_SC_CPWMS_MASK; 		/* up counting */
//	TPM1->CONTROLS[X].CnSC &= ~ (TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK);
//	TPM1->CONTROLS[X].CnSC |= (TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK); /* capture on both edges */ 
  
//	TPM1->CONTROLS[X].CnSC |= TPM_CnSC_CHIE_MASK; // ToDo 2.1.6: Enable interrupt on selected channel
	
	NVIC_SetPriority(TPM1_IRQn, 1);  /* TPM1 interrupt priority level  */

	NVIC_ClearPendingIRQ(TPM1_IRQn); 
	NVIC_EnableIRQ(TPM1_IRQn);	/* Enable Interrupts */

}

void TPM0_Init_PWM(void) {
		
//  SIM->SCGC6 |= SIM_SCGC6_XXX_MASK;		// ToDo 3.1.1: Enable TPM0 mask in SCGC6 register
//	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(X);  // ToDo 3.1.1: Choose MCGFLLCLK clock source

//	SIM->SCGC5 |= SIM_SCGC5_PORTX_MASK; // ToDo 3.1.2: Connect port B to clock
//	PORTB->PCR[X] = PORT_PCR_MUX(X);		// ToDo 3.1.2: Set multiplekser to TPM0 for PTB9, get channel number (page 148 of the Reference Manual)

//	TPM0->SC |= TPM_SC_PS(X);  					// ToDo 3.1.3: Set prescaler to 128
//	TPM0->SC |= TPM_SC_CMOD(X);					// ToDo 3.1.4: For TMP0, select the internal input clock source

//	TPM0->MOD = XX; 										// ToDo 3.1.5: Set modulo value to maximum value from slider
	
// ToDo 3.1.6: Connect correct channel from TPM0 for "Edge-aligned PWM Low-true pulses" mode
//	TPM0->SC &= ~TPM_SC_CPWMS_MASK; 		/* up counting */
//	TPM0->CONTROLS[X].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK); /* set Output on match, clear Output on reload */ 

//	TPM0->CONTROLS[X].CnV = 50; 				// ToDo 3.1.7: Set starting value to 50
	tpm0Enabled = 1;  /* set local flag */
}

uint32_t TPM1_GetVal(void) {
	return tpm1Diff;
}

void TPM0_SetVal(uint32_t value) {
	value = value - 1; 				/* because slider returns '1' as minimum */
//	if (tpm0Enabled) TPM0->CONTROLS[X].CnV = value;    // ToDo 3.1.8: Choose correct channel for PWM update.
}
/**
 * @brief Interrupt handler for TPM1.
 */
void TPM1_IRQHandler(void) {
	
	tpm1Old = tpm1New;
//	tpm1New = TPM1->CONTROLS[X].CnV & 0xFFFF;  // ToDo 2.4 Enable saving counter value
	tpm1Diff = tpm1New - tpm1Old;	/* calculate difference */
	
//	LED_Ctrl(LED_RED, LED_TOGGLE); // ToDo 2.1.7: Enable red led toggle
//	TPM1->CONTROLS[X].CnSC |= TPM_CnSC_CHF_MASK; // ToDo 2.1.8: Clear channel flag
}

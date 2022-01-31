/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file i2c.c
 * @author Koryciak
 * @date Sep 2020
 * @brief File containing definitions for I2C.
 * @ver 0.3
 */

#include "i2c.h"

/******************************************************************************\
* Private definitions
\******************************************************************************/
#define SCL   3
#define SDA   4
/******************************************************************************\
* Private prototypes
\******************************************************************************/
void i2c_m_start(void);
void i2c_m_stop(void);
void i2c_m_rstart(void);
void i2c_tran(void);
void i2c_rec(void);
void i2c_enable(void);
void i2c_disable(void);
void i2c_send(uint8_t);
uint8_t i2c_read(void);
void i2c_wait(void);
void i2c_NACK(void);
void i2c_ACK(void);
/******************************************************************************\
* Private memory declarations
\******************************************************************************/
static uint8_t error;
static uint16_t timeout;

void I2C_Init(void) {
	
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK ;					/* clock for I2C0  */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					/* clock for PORTB */
	
	PORTB->PCR[SCL] |= PORT_PCR_MUX(2); 				  /* I2C0 SCL	(PTB3) */
	PORTB->PCR[SDA] |= PORT_PCR_MUX(2); 					/* I2C0 SDA	(PTB4) */
	I2C0->C1 &= ~(I2C_C1_IICEN_MASK);								
	I2C0->F  |= I2C_F_MULT(1);
	I2C0->F  |= I2C_F_ICR(0x19);
	//I2C0->C1 |= I2C_C1_IICIE_MASK;
	//NVIC_ClearPendingIRQ(I2C0_IRQn);
	//NVIC_EnableIRQ(I2C0_IRQn);	
}

uint8_t I2C_Write(uint8_t address, uint8_t data) {
	
	error = 0x00;
	
	i2c_enable();
	i2c_tran();													/* set to transmit mode */
	i2c_m_start();											/* send start */
	i2c_send((uint8_t)(address << 1));  /* send slave address and write condition */
	i2c_wait();													/* wait for ack from salve */
	i2c_send(data);											/* send data */
	i2c_wait();													/* wait for completion of transfer with ack from slave  */
	i2c_m_stop();												/* send stop */
	i2c_disable();
	
	return error;
}

uint8_t I2C_Read(uint8_t address, uint8_t *ptr)
{
	error = 0x00;
	
	i2c_enable();
	i2c_tran();													/* set to transmite mode */
	i2c_m_start();											/* send start */
	i2c_send((uint8_t)((address << 1)|0x1));  /* send slave address and read condition */
	i2c_wait();													/* wait for ack from salve */
	i2c_rec();												/* set to receive mode */
	i2c_NACK();												/* send NACK after read */
	*ptr=i2c_read();									/* dummy read to start the transfer */
	i2c_wait();												/* wait for completion of transfer with no ack from master  */
	i2c_m_stop();											/* send stop */
	*ptr=i2c_read();									/* read data */
	i2c_disable();
	
	return error;
}
/**
 * @brief I2C master start.
 */
void i2c_m_start(void) {
  I2C0->C1 |= I2C_C1_MST_MASK;
}
/**
 * @brief I2C master stop.
 */
void i2c_m_stop(void) {
  I2C0->C1 &= ~I2C_C1_MST_MASK;
}
/**
 * @brief I2C master restart.
 */
void i2c_m_rstart(void) {
  I2C0->C1 |= I2C_C1_RSTA_MASK;
}
/**
 * @brief I2C transmit.
 */
void i2c_tran(void) {
  I2C0->C1 |= I2C_C1_TX_MASK;
}
/**
 * @brief I2C receive.
 */
void i2c_rec(void) {
  I2C0->C1 &= ~I2C_C1_TX_MASK;
}
/**
 * @brief I2C enable.
 */
void i2c_enable(void) {
  I2C0->C1 |= I2C_C1_IICEN_MASK;
}
/**
 * @brief I2C disable.
 */
void i2c_disable(void) {
  I2C0->C1 &= ~I2C_C1_IICEN_MASK;
}
/**
 * @brief I2C send data.
 */
void i2c_send(uint8_t data) {
	I2C0->D = data;
}
/**
 * @brief I2C read data.
 */
uint8_t i2c_read(void) {
	return I2C0->D;
}
/**
 * @brief I2C wait.
 */
void i2c_wait(void) {
  timeout = 0;
	
  while (((I2C0->S & I2C_S_IICIF_MASK)==0) && (timeout<10000)) timeout++;
  if (timeout >= 10000) 						  error |= I2C_ERR_TIMEOUT; 
	if ((I2C0->S & I2C_S_RXAK_MASK)==1) error |= I2C_ERR_NOACK;
	I2C0->S |= I2C_S_IICIF_MASK;
}
void i2c_NACK(void)
{
	I2C0->C1 |= I2C_C1_TXAK_MASK;
}

void i2c_ACK(void)
{
	I2C0->C1 &= (~I2C_C1_TXAK_MASK);
}

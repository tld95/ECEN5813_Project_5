/*
 *  PES Project Five UART0 Control header code implementation
 *	Tristan Duenas
 *	References:
 *	https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/inc/UART.h
 */

#ifndef __UART0_CONTROL_H__
#define __UART0_CONTROL_H__

#include <stdint.h>
#include "MKL25Z4.h"

// Referenced https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/Serial-Demo/inc/UART.h
#define UART_OVERSAMPLE_RATE 16
#define BUS_CLOCK 24e6

typedef enum parity
{
	EVEN,
	ODD,
	NONE
} Parity;

// UART0 Polling/Interrupt Shared
void uart0_Init(uint32_t baudRate, Parity parity);
uint8_t uart0_TransmitterAvailable();
void uart0_TransmitCharacter(uint8_t character);
uint8_t uart0_ReceiverCharacterAvailable();
uint8_t uart0_ReceiveCharacter();

// UART0 Polling
void uart0_PollingTransmitCharacterOnAvailablity(uint8_t character);
uint8_t uart0_PollingReceiveCharacterOnAvailability();
void uart0_PollingEchoCharacter();

// UART0 Interrupt
void UART0_IRQHandler();
void uart0_InterruptTransmitCharacterOnAvailablity();
void uart0_InterruptReceiveCharacterOnAvailability();
void uart0_InterruptCheckErrors();
void uart0_InterruptEchoCharacter();

#endif

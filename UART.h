/*
 * UART.h
 *
 *  Created on: Apr 22, 2018
 *      Author: truyen
 */

#ifndef UART_H_
#define UART_H_

unsigned int i=0;
//*****************************************************************************
void Clock_Config(void);
void IO_Config(void);
void Uart_Config(void);
void UARTSendString(char *text);

//*****************************************************************************

void Clock_Config(){
    {
        DCOCTL =0;
        BCSCTL1= CALBC1_12MHZ; // Set DCO to 12 MHz
        DCOCTL = CALDCO_12MHZ;
    }
}
//*****************************************************************************
void IO_Config(){
    P1DIR |= BIT0 + BIT6; // P1.0-TXLED and P1.6-RXLED output
    P1OUT &= ~(BIT0 + BIT6); //P1.0 and P1.6 = 0
}
//*****************************************************************************
void Uart_Config(){
    P1SEL = BIT1 + BIT2 ;               // Select UART RX/TX function on P1.1,P1.2
    P1SEL2 = BIT1 + BIT2;

    UCA0CTL1 |= UCSSEL_2;               // UART Clock -> SMCLK
    UCA0BR0 = 104;                      // Baud Rate Setting for 12MHz 115200
    UCA0BR1 = 0;                        // Baud Rate Setting for 12MHz 115200
    UCA0MCTL = UCBRS_1;                 // Modulation Setting for 12MHz 115200
    UCA0CTL1 &= ~UCSWRST;               // Initialize UART Module

     IE2 |= UCA0RXIE;                   // Enable USCI_A0 RX interrupt
     _BIS_SR(GIE);
}
//*****************************************************************************
void UARTSendString(char *text)
{
    i = 0;
    while(text[i] != '\0')              // Check for end of string
    {
        while (!(IFG2&UCA0TXIFG));      // Check if TX is ongoing
        UCA0TXBUF = text[i];            // TX -> current char
        i++;                            // Increment counter
        P1OUT ^= BIT0;                  //
    }
}
#endif /* UART_H_ */

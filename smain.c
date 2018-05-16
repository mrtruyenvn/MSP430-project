#include <msp430.h>
#include<mymath.h>
#include<mystring.h>
#include<UART.h>
//*****************************************************************************************************
//Dinh nghia bien
float xx, yy;
float xxx;

char Name0[] = "UIT";
char cRSSI0[2];
unsigned int count_Name0 = 0;
unsigned int count_RSSI0 = 0;

char Name1[] = "UIT Public";
char cRSSI1[2];
unsigned int count_Name1 = 0;
unsigned int count_RSSI1 = 0;

char Name2[] = "UIT-GUEST";
char cRSSI2[2];
unsigned int count_Name2 = 0;
unsigned int count_RSSI2 = 0;

unsigned int length0 = 0;
unsigned int length1 = 0;
unsigned int length2 = 0;

int iRSSI0 = 0;
int iRSSI1 = 0;
int iRSSI2 = 0;

float Distance0 = 0;
float Distance1 = 0;
float Distance2 = 0;
//************************************************************************************
//Ham Main

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Stop Watchdog
    Clock_Config();
    IO_Config();
    Uart_Config();

    length0 =mystrlen(Name0);
    length1 = mystrlen(Name1);
    length2 = mystrlen(Name2);

    UARTSendString("AT+RST\r\n");
    __delay_cycles(50000000);

//    UARTSendString("AT+CWMODE=1\r\n");
//       __delay_cycles(50000000);
//
//    UARTSendString("AT+CWLAP\r\n");
//    __delay_cycles(60000000);
//    UARTSendString("AT+CWLAP\r\n");
//    __delay_cycles(60000000);
//    UARTSendString("AT+CWLAP\r\n");
//    __delay_cycles(60000000);

    iRSSI0 = (-1) * mystrtoint(cRSSI0);
    Distance0 = getDistances(iRSSI0, 2412);

    iRSSI1 = (-1) * mystrtoint(cRSSI1);
    Distance1 = getDistances(iRSSI1, 2412);

    iRSSI2 = (-1) * mystrtoint(cRSSI2);
    Distance2 = getDistances(iRSSI2, 2412);

    getTrilateration(&xx, &yy, 0, 0, 480, 960, 240, 540, Distance0, Distance1, Distance2);


    //    int place = 14445;
    //    char buffer[30];
    //    sprintf(buffer,"%d",place);
    //    lenx= strlen(buffer);

        UARTSendString("AT+CWQAP\r\n");
        __delay_cycles(50000000);
        UARTSendString("AT+CWJAP=\"TruyenXuanNguyen\",\"12345678\"\r\n");
        __delay_cycles(180000000);
        UARTSendString("AT+CIPSTART=\"TCP\",\"192.168.4.1\",5000\r\n");
        __delay_cycles(80000000);
        UARTSendString("AT+CIPSEND=6\r\n");
        __delay_cycles(30000000);
        UARTSendString("Tu,1,2");
    while (1)
    {
        _no_operation();
    }

}

//*****************************************************************************************************
//Ham ngat de truyen ve RSSI
#pragma vector = USCIAB0RX_VECTOR
__interrupt void RecUART(void)
{
    if (count_Name0 == length0)
    {
        P1OUT ^= BIT6;

        if (UCA0RXBUF >= '0' && UCA0RXBUF <= '9' && count_RSSI0 < 2)
        {
            cRSSI0[count_RSSI0] = UCA0RXBUF;
            count_RSSI0++;
        }
    }
    else if (count_Name0 != length0)
    {
        if (UCA0RXBUF == Name0[count_Name0])
        {
            count_Name0++;

        }
        else
        {
            count_Name0 = 0;
            count_RSSI0 = 0;
        }
    }

    if (count_Name1 == length1)
    {
        P1OUT ^= BIT6;

        if (UCA0RXBUF >= '0' && UCA0RXBUF <= '9' && count_RSSI1 < 2)
        {
            cRSSI1[count_RSSI1] = UCA0RXBUF;
            count_RSSI1++;
        }
    }
    else if (count_Name1 != length1)
    {
        if (UCA0RXBUF == Name1[count_Name1])
        {
            count_Name1++;

        }
        else
        {
            count_Name1 = 0;
            count_RSSI1 = 0;
        }
    }

    if (count_Name2 == length2)
    {
        P1OUT ^= BIT6;

        if (UCA0RXBUF >= '0' && UCA0RXBUF <= '9' && count_RSSI2 < 2)
        {
            cRSSI2[count_RSSI2] = UCA0RXBUF;
            count_RSSI2++;
        }
    }
    else if (count_Name2 != length2)
    {
        if (UCA0RXBUF == Name2[count_Name2])
        {
            count_Name2++;

        }
        else
        {
            count_Name2 = 0;
            count_RSSI2 = 0;
        }
    }
    IFG2 &= ~UCA0RXIFG;
}

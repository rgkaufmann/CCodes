#include "msp430.h"

#define TXD             BIT2
#define RXD             BIT1

void main(void)
{
  volatile unsigned int speedmeasure = 0;
  WDTCTL = WDTPW + WDTHOLD;

  P1DIR = 0x00;
  P1DIR |= TXD;
  P1OUT = TXD;

  ADC10CTL1 = INCH_4;
  ADC10CTL0 = ADC10SHT_3 + ADC10ON;

  P1SEL = RXD + TXD;
  P1SEL2 = RXD + TXD;
  UCA0CTL1 |= UCSSEL_2;
  UCA0BR0 = 104;
  UCA0BR1 = 0;
  UCA0MCTL = UCBRS0;
  UCA0CTL1 &= ~UCSWRST;

  while(1)
  {
    speedmeasure = 0;
    for(unsigned int i = 0; i < 20; i++)
    {
      ADC10CTL0 |= ENC + ADC10SC;
      while(ADC10CTL1 &ADC10BUSY);
      speedmeasure += ADC10MEM;
      ADC10CTL &= ~ENC;
      __delay_cycles(1000);
    }
    speedmeasure = speedmeasure/20;

    while(!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = speedmeasure;
    speedmeasure = speedmeasure>>8;
    while(!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = speedmeasure;

    __delay_cycles(1000);
  }
}

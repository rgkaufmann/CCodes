#include "msp430.h"

#define ECHO BIT4
#define PULSE BIT7

#define TXD BIT2
#define RXD BIT1

void main(void)
{
  unsigned long timeMeasured = 0;
  WDTCTL = WDTPW + WDTHOLD;

  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  BCSCTL2 &= ~(DIVS_3);

  P1DIR |= ~(ECHO+RXD);
  P1OUT = TXD;

  __delay_cycles(1000);

  P1SEL = RXD + TXD;
  P1SEL2 = RXD + TXD;
  UCA0CTL1 |= UCSSEL_2;
  UCA0BR0 = 104;
  UCA0BR1 = 0;
  UCA0MCTL = UCBRS0;
  UCA0CTL1 &= ~UCSWRST;

  TACTL = TASSEL_2 + MC_2;

  while (1)
  {
    P1OUT ^= PULSE;
    __delay_cycles(10);
    P1OUT ^= PULSE;

    while (!(P1IN & ECHO)) TAR = 0;
    while (P1IN & ECHO) timeMeasured = TAR;

    while (!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = timeMeasured;
    while (!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = timeMeasured>>8;

    __delay_cycles(50000);
  }
}

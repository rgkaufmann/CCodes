//******************************************************************************
//  MSP430G2x31 Demo - ADC10, Sample A1, AVcc Ref, Set P1.0 if > 0.75*AVcc
//
//  Description: A single sample is made on A1 with reference to AVcc.
//  Software sets ADC10SC to start sample and conversion - ADC10SC
//  automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
//  and conversion.
//
//                MSP430G2x31
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|
//            |                 |
//            |                 |
//            |                 |
//            |                 |
//            |                 |
// input  >---|P1.1/A1      P1.0|--> red Led onboard BIT0
//            |                 |
//            |             P1.2|--> yellow Led
//            |             P1.6|--> green Led onboard BIT6
//
//
//  D. Dang
//  Texas Instruments Inc.
//******************************************************************************
#include "msp430.h"

#define TXD             BIT2
#define RXD             BIT1

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10SHT_2 + ADC10ON; 	    // ADC10ON
  ADC10CTL1 = INCH_3;                       // input A1
  ADC10AE0 |= 0x02;                         // PA.1 ADC option select
  P1DIR |= 0x45;                            // Set port inputs and outputs

  P1DIR |= ~RXD;
  P1OUT = TXD;

  P1SEL = RXD + TXD;
  P1SEL2 = RXD + TXD;
  UCA0CTL1 |= UCSSEL_2;
  UCA0BR0 = 104;
  UCA0BR1 = 0;
  UCA0MCTL = UCBRS0;
  UCA0CTL1 &= ~UCSWRST;

  for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;            // Sampling and conversion start
    while (ADC10CTL1 &ADC10BUSY);          // ADC10BUSY?
    if (ADC10MEM > 0x3FF) {
      P1OUT &= ~0x01;                       // Clear P1.0 LED off
      P1OUT &= ~0x04;                       // Clear P1.2 LED off
      P1OUT &= ~0x40;                       // Clear P1.6 LED off

    }
    else if (ADC10MEM < 0x0F8) {
      P1OUT &= ~0x01;                       // Clear P1.0 LED off
      P1OUT &= ~0x04;                       // Clear P1.2 LED off
      P1OUT |= 0x40;                        // Set P1.6 LED on
    }
    else if (ADC10MEM > 0x26C) {
      P1OUT &= ~0x04;                       // Clear P1.2 LED off
      P1OUT &= ~0x40;                       // Clear P1.6 LED off
      P1OUT |= 0x01;                        // Set P1.0 LED on
    }
    else {
      P1OUT &= ~0x40;                       // Clear P1.6 LED off
      P1OUT &= ~0x01;                       // Clear P1.0 LED off
      P1OUT |= 0x04;                        // Set P1.2 LED on
    }

    while(!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = ADC10MEM;

    unsigned i;
    for (i = 0xFFFF; i > 0; i--);          // Delay
  }
}
//******************************************************************************

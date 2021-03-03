#include "msp430.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;         // Stop WDT

  ADC10CTL0 = ADC10SHT_2 + ADC10ON; // ADC10ON
  ADC10CTL1 = INCH_1;               // Input A1
  ADC10AE0 |= 0x02;                 // PA.1 ADC option select

  P1DIR |= BIT2;                    // P1.2 to output
  P1SEL |= BIT2;                    // P1.2 to TA0.1

  CCR0 = 500-1;                    // PWM Period to 500
  CCTL1 = OUTMOD_7;                 // CCR1 reset/set
  TACTL = TASSEL_2 + MC_1;          // SMCLK to up mode

  for (;;)                          // Infinite Loop
  {
    ADC10CTL0 |= ENC + ADC10SC;     // Sampling and Conversion Start
    while (ADC10CTL1 &ADC10BUSY);   // ADC10BUSY?
    CCR1 = ((ADC10MEM*10)/(33));   // Set CCR1 Duty cycle
    if (ADC10MEM < 0x010)
      CCR1 = 0;
    for (unsigned i = 0xFFFF; i>0; i--); // Delay
  }
}

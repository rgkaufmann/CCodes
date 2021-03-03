#include "msp430.h"

#define UNIT 5000

void wait(unsigned int wait)
{
	volatile unsigned int count = UNIT;
	for (wait; wait>0; wait--)
	{
		count = UNIT;
		while (count>0)
			count--;
	}
}

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;

	P1DIR |= BIT2;
	P1SEL |= BIT2;

	CCR0 = 2500-1;
	CCTL1 = OUTMOD_7;
	TACTL = TASSEL_2 + MC_1;
	CCR1 = 0;

	volatile unsigned int message[64] = {1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 2, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 3, 2, 1, 2, 1, 2, 7, 1, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 1, 1, 2, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 3, 2, 1, 1, 1, 1, 7};
	volatile unsigned int indx = 0;

	for(unsigned int i = 32; i>0; i--)	{
		CCR0 = 2500-1;
		CCTL1 = OUTMOD_7;
		CCR1 = 1500;
		TACTL = TASSEL_2 + MC_1;
		wait(message[indx]);
		indx++;

		CCR0 = 1-1;
		CCTL1 = OUTMOD_7;
		TACTL = TASSEL_2 + MC_1;
		CCR1 = 0;
		wait(message[indx]);
		indx++;
	}

	CCR0 = 1-1;
	CCTL1 = OUTMOD_7;
	TACTL = TASSEL_2 + MC_1;
	CCR1 = 0;
	_BIS_SR(LPM0_bits);
}

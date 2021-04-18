#include <msp430.h>
#include "stdint.h"
int cnt =0;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;       //desactivation Watch Dog Timer
  BCSCTL1= CALBC1_1MHZ;           //frequence d'horloge 1MHz
  DCOCTL= CALDCO_1MHZ;            // "
  P1DIR |= BIT0;                  //bit 0 port 1 en sortie
  TA0CTL = 0|(TASSEL_2 | ID_0);   //source SMCLK, pas de predivision ID_0
  TA0CTL |= MC_1;                 //comptage en mode up
  TA0CTL |= TAIE;                 //autorisation interruption TAIE
  TA0CCR0 = 49999;                //voir texte   1/1mhz * 50000  0.5s
  __enable_interrupt();
  while(1)                        //boucle infinie ou le programme peut faire autre chose
  {
  }
}


#pragma vector=TIMER0_A1_VECTOR   
__interrupt void ma_fnc_timer(void)
{
    cnt ++;
    if(cnt==20)
    {
        cnt =0;
        P1OUT ^= BIT0;            //changement d'etat LED rouge
    }
    TA0CTL &= ~TAIFG;//RAZ TAIFG
}


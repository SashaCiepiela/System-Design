#include "Initialisation.h"

void Initialisation (void)
{
   //Clock (Fosc) a 8Mhz, On configure "OSCILLATOR CONTROL REGISTER" pou rd�terminer la fr�quence de l'horloge interne (p30 Datasheet)
   OSCCONbits.IRCF0 = 1 ; //La choix IRCF0 permet de choisir la fr�quence d'oscillation interne
   OSCCONbits.IRCF1 = 1 ;
   OSCCONbits.IRCF2 = 1 ;
}

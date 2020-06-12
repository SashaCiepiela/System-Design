//#include "Initialisation.h"
#include "lib.h"

void Initialisation (void)
{
   //Clock (Fosc) a 8Mhz, On configure "OSCILLATOR CONTROL REGISTER" pou rdéterminer la fréquence de l'horloge interne (p30 Datasheet)
   OSCCONbits.IRCF0 = 1 ; //La choix IRCF0 permet de choisir la fréquence d'oscillation interne
   OSCCONbits.IRCF1 = 1 ;
   OSCCONbits.IRCF2 = 1 ;

    //####################################
    //Inititialisation Mesure_batterie()
    //Initialisation du pins de VBATT (RA2)
    PORTAbits.AN2 = 1; //On initialise le port an2 en input
    PORTAbits.AN3 = 1; //On initialise le port an3 en input (ce qui nous permet de l'utiliser comme vref+ pour la conversion)
    //Faut-il mettre an0 an1 et an3 en input???

    //Initialisation de la conversion analogique vers numérique
    ADCON1bits.PCFG3 = 1; // On initialise les pin AN0,AN1,AN2,AN3 en analogique (p224 Datasheet)
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 1;

    ADCON0bits.CHS3 = 0; //Selection de la voie ANx. On règle l'entrée du multiplexeur sur l'entrée AN2 (p223 Datasheet)
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS0 = 0;

    ADCON1bits.VCFG0 = 1; //L'entrée AN3 est utilisé comme vref+
    ADCON1bits.VCFG0 = 0; // Met le Vref- sur la masse Vss

    ADCON2bits.ADCS2 = 0; //On configure Tad le plus faible possible pour avoir la conversion la plus rapide possible (une conversion se fait sur 11Tad) mais supérieur à 0,7µs pour des raisons matériels)
    ADCON2bits.ADCS1 = 0; //Pn a donc choisi de diviser Fosc par 8 nous donnant un Tad=1µs
    ADCON2bits.ADCS0 = 1;

    ADCON2bits.ACQT2 = 0; //On calcul Tacq = 4,2µs on obtient donc le temps total de l'acquisition et conversion faisans 5,2*Tad donc on arrondit à la borne supérieur pour prendre 6*Tad
    ADCON2bits.ACQT1 = 1;
    ADCON2bits.ACQT0 = 1;

    ADCON2bits.ADFM = 1; //On veut que la donnée soit justifiée à droite
}

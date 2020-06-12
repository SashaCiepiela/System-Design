//#include "Initialisation.h"
#include "lib.h"

void Initialisation (void)
{
   //Clock (Fosc) a 8Mhz, On configure "OSCILLATOR CONTROL REGISTER" pou rd�terminer la fr�quence de l'horloge interne (p30 Datasheet)
   OSCCONbits.IRCF0 = 1 ; //La choix IRCF0 permet de choisir la fr�quence d'oscillation interne
   OSCCONbits.IRCF1 = 1 ;
   OSCCONbits.IRCF2 = 1 ;

    //####################################
    //Inititialisation Mesure_batterie()
    //Initialisation du pins de VBATT (RA2)
    PORTAbits.AN2 = 1; //On initialise le port an2 en input
    PORTAbits.AN3 = 1; //On initialise le port an3 en input (ce qui nous permet de l'utiliser comme vref+ pour la conversion)
    //Faut-il mettre an0 an1 et an3 en input???

    //Initialisation de la conversion analogique vers num�rique
    ADCON1bits.PCFG3 = 1; // On initialise les pin AN0,AN1,AN2,AN3 en analogique (p224 Datasheet)
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 1;

    ADCON0bits.CHS3 = 0; //Selection de la voie ANx. On r�gle l'entr�e du multiplexeur sur l'entr�e AN2 (p223 Datasheet)
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS0 = 0;

    ADCON1bits.VCFG0 = 1; //L'entr�e AN3 est utilis� comme vref+
    ADCON1bits.VCFG0 = 0; // Met le Vref- sur la masse Vss

    ADCON2bits.ADCS2 = 0; //On configure Tad le plus faible possible pour avoir la conversion la plus rapide possible (une conversion se fait sur 11Tad) mais sup�rieur � 0,7�s pour des raisons mat�riels)
    ADCON2bits.ADCS1 = 0; //Pn a donc choisi de diviser Fosc par 8 nous donnant un Tad=1�s
    ADCON2bits.ADCS0 = 1;

    ADCON2bits.ACQT2 = 0; //On calcul Tacq = 4,2�s on obtient donc le temps total de l'acquisition et conversion faisans 5,2*Tad donc on arrondit � la borne sup�rieur pour prendre 6*Tad
    ADCON2bits.ACQT1 = 1;
    ADCON2bits.ACQT0 = 1;

    ADCON2bits.ADFM = 1; //On veut que la donn�e soit justifi�e � droite
}

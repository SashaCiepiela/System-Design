#include "lib.h"
#pragma config OSC = INTIO67 //bits de configurations de l'horloge, on va utiliser le bloc d'horloge interne. Elle est moins précise mais permet d'économiser un quartz et libérer 2 pins
#pragma config PBADEN = OFF /*met les pins configuré en digital (On = analogique) (p253 Datasheet)*/, WDT = OFF /*WatchDogTimer, si tout va bien le CPU va envoyer de manière régulière un signal au WDT pour dire que tout va bien, celui est généralement une pièce hardware. Si le signal n'est pas envoyé par le CPU au bout d'un certain temps determiné en fonction des WDT et pouvant parfois être configurable en fonction des uc, cela signifie que le CPU a fait face à un problème. Dans ce cas le WDT va initialiser un reset et/ou une serie de fonction pouvant permettre la résolution du problème */, LVP = OFF /*Low voltage programing, p266 Datasheet*/, DEBUG = ON /* On se place en mode débug*/

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

    //#################################
    //Initialisation uart
    BAUDCONbits.BRG16 = 0; //Le baudrate est généré sur 8 bits (p205 Datasheet)
    TXSTAbits.BRGH = 1; //On met le baudrate en high speed
    TXSTAbits.SYNC = 0; //On se place en mode asynchrone car le cable reliant le p18f2520 et l'ordinateur est long donc on est obligé de se mettre en mode asynchrone pour ne pas avoir de problèmes lors de la transmision de la data

    SPBRG = 0x33; // BRGH16 = 0 et BRGH = 1 => BR = Fosc/(16(SPBRG+1)) Donc SPBRG = 51(10) = 33(16)

    TRISCbits.RC6 = 0; //RC6 en input, ils sont déjà en mode digital grâce à PBADEN = OFF
    TRISCbits.RC7 = 0; //RC7 en input

    RCSTAbits.SPEN = 1; //Serial port enabled (configures RX/DT and TX/CK pins as serial port pins, permet de configurer le mode en RX in et TX out  (p203 Datasheet)
    TXSTAbits.TXEN = 1; //Active la transmition


    //######################################
    //Initialisation I2C
        //Configuration du registre SSPSTAT
    SSPSTAT = 0x80;
        //SSPSTATbits.SMP = 1; //Les données sont placées à la fin du temps de l'output (p166 Datasheet)
        //SSPSTATbits.CKE = 0; //Paramétrage du niveau par défaut de la clock et quand celle si passe au niveau opposé (ce paramètre conjointement avec ckp) (p166 Datasheet)
    SSPCON1 = 0x28; //(p172 Datasheet)
        //SSPCON1bits.WCOL = 0; // Write Collision Detected bit On ne prend pas en compte les collisions
        //SSPCON1bits.SSPOV = 0; //Pas d'overflow
        //SSPCON1bits.SSPEN = 1; //Utilise les ports de séries SDA et SCL, ils doivent cependant être configuré en input our output
        //SSPCON1bits.CKP = 0; //permet le clock stretch, l'esclave pourra donc laisser la clock à son niveau bas si il a besoin de temps, tant que la clock ne remonte pas, le master attend
        //SSPCON1bits."SSPM" = 1000; //En mode master la clock = FOSC/(4 * (SSPADD + 1))
    SSPCON2 = 0x00;
    SSPADD = 0x27; // Baudrate = Fosc/ (4 *(SSPADD+1)), Fosc = 8Mhz donc SSPADD =39(10) =27(16)


    printf (" FIN INI ");
}

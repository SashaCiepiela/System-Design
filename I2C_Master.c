#include "lib.h"
#include <i2c.h>
/* */


char  Lire_I2C_telecommande (Glob_var *glob_var) //ajouter de l'analyse de données
{
    char adresse_i2c = 0xA2; //adresse physique du bloc réception de la télecommande (cf datasheet Spec_Telecommande)
    char index = 0;
    while ( (SSPCON2&0x1F) | (SSPSTATbits.R_W)); //Vérifie que l'on est bien en idle donc que le cannal i2c ne soit pas utilisé
    SSPCON2bits.SEN= 1; //envoie la condition de start
    while (SSPCON2bits.SEN); //attente de la fin de la start condition
    SSPBUF = adresse_i2c +1 ; // envoie de l'adresse +1 car la telecommande est en mode ecriture
    while(SSPSTATbits.BF); //attente que le buffer soit vide
    while(SSPCON2bits.ACKSTAT); //Attente de l'acknowledge du slave
    
    do
    {
        while ((SSPCON2 & 0x1F) || (SSPSTATbits.R_W));  // ensure module is idle
	 	
	SSPCON2bits.RCEN=1;        // SSPBUF en reception
	while(!SSPSTATbits.BF);	// Attente buffer RX plein
	glob_var->Buff_lecture[index] = SSPBUF;		// Ecrit octet, la donnée reçu par le maitre est A 0X31 0X3y 00 (y = 1 à 5 selon la touche valide)
	if(SSPBUF)
		SSPCON2bits.ACKDT=0;        // initiate ACK
	else
		SSPCON2bits.ACKDT=1;        // initiate NoACK
	SSPCON2bits.ACKEN=1;
	while(SSPCON2bits.ACKEN);	// Attendre fin ACKEN
    }while(glob_var->Buff_lecture[index++]);	//Tant que not \'0'

    while ((SSPCON2 & 0x1F) || (SSPSTATbits.R_W));  // ensure module is idle
    SSPCON2bits.PEN=1;                  // send STOP condition
    while ( SSPCON2bits.PEN );  // attente fin stop condition

    PIR1bits.SSPIF = 0;				//Remise à jour du flag pour IT Stop
    return (0); 		// return with contents of SSPBUF


}
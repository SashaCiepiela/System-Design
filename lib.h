/* 
 * File:   lib.h
 * Author: arsen
 *
 * Created on 11 juin 2020, 16:51
 * Contient les bibliothèques nécessaire au code et le header correspondant aux différentes fonctions créent
 */

#ifndef LIB_H
#define	LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h> //permet de faire des opérations avec des exponentiels
#include <p18f2520.h> //Contient les registres du microcontroleur

//#include "Initialisation.h" //fonctionne pas pour une raison inconnue
//#include "Mesure_batterie.h"
//#include "I2C_Master.h"

typedef struct{
    volatile char Buff_lecture[100];
    volatile unsigned char i;
    volatile int v_batt;
}Glob_var;

#endif	/* LIB_H */


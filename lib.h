/* 
 * File:   lib.h
 * Author: arsen
 *
 * Created on 11 juin 2020, 16:51
 * Contient les biblioth�ques n�cessaire au code et le header correspondant aux diff�rentes fonctions cr�ent
 */

#ifndef LIB_H
#define	LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h> //permet de faire des op�rations avec des exponentiels
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


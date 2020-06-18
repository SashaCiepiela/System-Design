/* 
 * File:   main.c
 * Author: arsen
 *
 * Created on 11 juin 2020, 16:49
 */


#include "lib.h"
#include "Initialisation.h"
#include "Mesure_batterie.h"
#include "I2C_Master.h"
//#include "uart.h"

/*
 * 
 */


void main(void)
{
    Glob_var *glob_var;
    glob_var->i = 0;


    Initialisation();
    while (1)
    {

        Lire_I2C_telecommande(glob_var);
        Mesure_batterie(glob_var);
        //traitement de la donnée envoyée par la télécommande

    }
    
}


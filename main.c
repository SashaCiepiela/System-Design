/* 
 * File:   main.c
 * Author: arsen
 *
 * Created on 11 juin 2020, 16:49
 */


#include "lib.h"


/*
 * 
 */
void main(void)
{
    Initialisation();
    while (1)
    {
        Mesure_batterie();
    }
    Mesure_batterie();
//    printf("wtf");
    
}


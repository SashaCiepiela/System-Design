/* 
 * File:   Initialisation.h
 * Author: arsen
 *
 * Created on 11 juin 2020, 18:55
 * Contient le nécessaire à l'initialisation du microcontroleur p18f2520
 * L'horloge est initialisée et réglée sur 8MHz
 */

#ifndef INITIALISATION_H
#define	INITIALISATION_H

#pragma config OSC = INTIO67 //bits de configurations de l'horloge, on va utiliser le bloc d'horloge interne. Elle est moins précise mais permet d'économiser un quartz et libérer 2 pins
#pragma config PBADEN = OFF /*met les pins configuré en digital (On = analogique) (p253 Datasheet)*/, WDT = OFF /*WatchDogTimer, si tout va bien le CPU va envoyer de manière régulière un signal au WDT pour dire que tout va bien, celui est généralement une pièce hardware. Si le signal n'est pas envoyé par le CPU au bout d'un certain temps determiné en fonction des WDT et pouvant parfois être configurable en fonction des uc, cela signifie que le CPU a fait face à un problème. Dans ce cas le WDT va initialiser un reset et/ou une serie de fonction pouvant permettre la résolution du problème */, LVP = OFF /*Low voltage programing, p266 Datasheet*/, DEBUG = ON /* On se place en mode débug*/
void Initialisation (void) ;

#endif


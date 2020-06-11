/* 
 * File:   Initialisation.h
 * Author: arsen
 *
 * Created on 11 juin 2020, 18:55
 * Contient le n�cessaire � l'initialisation du microcontroleur p18f2520
 * L'horloge est initialis�e et r�gl�e sur 8MHz
 */

#ifndef INITIALISATION_H
#define	INITIALISATION_H

#pragma config OSC = INTIO67 //bits de configurations de l'horloge, on va utiliser le bloc d'horloge interne. Elle est moins pr�cise mais permet d'�conomiser un quartz et lib�rer 2 pins
#pragma config PBADEN = OFF /*met les pins configur� en digital (On = analogique) (p253 Datasheet)*/, WDT = OFF /*WatchDogTimer, si tout va bien le CPU va envoyer de mani�re r�guli�re un signal au WDT pour dire que tout va bien, celui est g�n�ralement une pi�ce hardware. Si le signal n'est pas envoy� par le CPU au bout d'un certain temps determin� en fonction des WDT et pouvant parfois �tre configurable en fonction des uc, cela signifie que le CPU a fait face � un probl�me. Dans ce cas le WDT va initialiser un reset et/ou une serie de fonction pouvant permettre la r�solution du probl�me */, LVP = OFF /*Low voltage programing, p266 Datasheet*/, DEBUG = ON /* On se place en mode d�bug*/
void Initialisation (void) ;

#endif


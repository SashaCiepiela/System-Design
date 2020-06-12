#include "lib.h"
//Afficher le résultat à travers un cannal re-232

void Mesure_batterie (void)
{

    //Initialisation des variables
    int vbatt[4]; //Tableau dans lequel on va stocker les tensions de la batterie à différents instants. On va utiliser ces différentes valeurs pour faire la moyenne, cette moyenne est faite sur 4 mesures (cahier de charge)
    int vbatt_moy; //variable contenant la valeur moyenne de la tension sur 4 mesures
    int i =0; //indice du tableau ou l'on est
    int n;

    ADCON0bits.ADON = 1; //On met en route le convertisseur
    
    while (ADCON0bits.DONE)
    {
        //Met la valeur de la batterie dans la variable
        vbatt[i]= (ADRES/(pow(2,10)-1)*(16-5))+5 ;//Problème on ne connait pas la valeur de vref+
        //remise à zéro de vbatt_moy
        vbatt_moy = 0;
        if (i=3)
            i =0;
        else
            i++;
        n=0;
        while (n<4)
        {
            vbatt_moy += vbatt[n];
            n++;
        }
        vbatt_moy = vbatt_moy /4;

//            printf("VBATT = %d \n", vbatt_moy);
    }
 

}

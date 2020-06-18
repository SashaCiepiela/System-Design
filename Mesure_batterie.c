//Afficher le r�sultat � travers un cannal RS-232
//Les 3 premi�res donn�es ne sont pas fiable (�tant donn�e que la moyenne se fait sur 4 donn�es, les premi�res fois la valeur envoy� sera une donn�e al�atoire)
//On peut am�liorer le programme en ajoutant un signal lumineux si la batterie est d�charg�e

#include "lib.h"
//#include "uart.h"


void Mesure_batterie (Glob_var *glob_var)
{

    //Initialisation des variables
    int vbatt[4]; //Tableau dans lequel on va stocker les tensions de la batterie � diff�rents instants. On va utiliser ces diff�rentes valeurs pour faire la moyenne, cette moyenne est faite sur 4 mesures (cahier de charge)
    int vbatt_moy; //variable contenant la valeur moyenne de la tension sur 4 mesures
    int i =0; //indice du tableau ou l'on est
    int n;
    
    ADCON0bits.ADON = 1; //On met en route le convertisseur
    
    while (ADCON0bits.DONE)
    {
        //Met la valeur de la batterie dans la variable
        vbatt[i]= (ADRES/(pow(2,10)-1)*(16-5))+5 ;
        vbatt_moy = 0; //remise � z�ro de vbatt_moy

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
    }

    glob_var->v_batt = vbatt_moy;
    printf ("vbatt_moy = %d ", vbatt_moy);
}

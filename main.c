#include <stdio.h>
#include <stdlib.h>
#include "liste.h"



void main()
{
    int choix;
    struct liste L;
    creer_liste(&L);


    do {
        printf("MENU GENERAL \n\n");
        printf("1/ Creation de repertoire telephonique \n");
        printf("2/ Mise a jour des telephones \n");
        printf("3/ Recherche, affichage et tri \n");
        printf("4/ Enregistrement et chargement dans un fichier \n");
        printf("5/ Quitter \n\n");



        printf("Donner votre choix SVP : ");
        scanf("%d",&choix);
        printf("\n");

        switch(choix)
        {
            case 1:
                CREATION(&L);
                break;
            case 2:
                if(taille_liste(&L)!=0)
                    MISE_A_JOUR(&L);
                else
                    printf("Le repertoire est vide ! \n");
                break;
            case 3:
                if(taille_liste(&L)!=0)
                    RECH_AFF(&L);
                else
                    printf("Le repertoire est vide ! \n");
                break;
            case 4:
                ENRE_CHAR(&L);
                break;
            case 5:
                printf("Fin du programme\n");
                exit(0);
                break;
            default:
                printf("CHOIX INVALIDE. \n\n\n");
        }
    printf("\n");
    } while(choix != 5);
}

#include <stdlib.h>
#include <stdio.h>
#include "assist_en.h"
#include "menu1_en.h"
#include "menu2_en.h"
#include "menu3_en.h"
#include "menu4_en.h"
#include "menu5_en.h"
#define TAILLE_MAX 1000 //tableau de taille 1000

int my_debut(FILE *fichier)
{
    char chaine[TAILLE_MAX] = ""; //chaine vide de TAILLE_MAX
    if (fichier != NULL)
    {
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL) donc tant qu'on arrive pas à la fin

        {
            printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
        }
    }
}

int my_menus(int *choix, FILE *fichier)//l'utilisateur choisi entre les différentes options
{
    int i = 0;
    int a = 0;
    int *pa = &a;
    int b = 0;
    int *pro = &b;
    int c = 0;
    int *ca = &c;
    int d = 0;
    int *pl = &d;
    int e = 0;
    int *pf = &e; 

    //system("clear");
    switch(*choix)
    {
        case 1 : //Si 1 alors afficher menu 1
        fclose(fichier);
        fichier = fopen("MenusEN/menu1en", "r");
        my_debut(fichier);
        scanf("%d", &a);
        fflush(stdin);
        processus(pa, fichier);
        break;

        case 2 : //Si 2 alors afficher menu 2
        fclose(fichier);
        fichier = fopen("MenusEN/menu2en", "r");
        my_debut(fichier);        
        scanf("%d", &b);
        fflush(stdin);
        programmes(pro, fichier);
        break;

        case 3 : //Si 3 alors afficher menu 3
        fclose(fichier);
        fichier = fopen("MenusEN/menu3en", "r");
        my_debut(fichier);
        scanf("%d", &c);
        fflush(stdin);
        my_azerty(ca, fichier);
        break;

        case 4 : //Si 4 alors afficher menu 4
        fclose(fichier);
        fichier = fopen("MenusEN/menu4en", "r");
        my_debut(fichier);
        scanf("%d", &d);
        fflush(stdin);
        periph(pl, fichier);
        break;

        case 5 : //Si 5 alors afficher menu 5
        fclose(fichier);
        fichier = fopen("MenusEN/menu5en", "r");
        my_debut(fichier);
        scanf("%d", &e);
        fflush(stdin);
        my_file(pf, fichier);
        break;

        default :
        printf("\nError\n");
        break;
    }
    return 0;
}



int assist_en()
{
    system("clear");//on fait un clear au démarrage
    int choix = 0;
    FILE *fichier = NULL;
    fichier = fopen("MenusEN/menu0en", "r"); //Dans le main pour etre affiché en premier
    my_debut(fichier); //pour afficher le fichier
    scanf("%d", &choix); //Pour demander le choix du menu$
    system("clear");
    my_menus(&choix, fichier);

    return 1;
}

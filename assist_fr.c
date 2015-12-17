#include <stdlib.h>
#include <stdio.h>
#include "assist_fr.h"
#include "menu1_fr.h"
#include "menu2_fr.h"
#include "menu3_fr.h"
#include "menu4_fr.h"
#include "menu5_fr.h"
#define TAILLE_MAX 1000 //tableau de taille 1000

int fr_debut(FILE *frfichier)
{
    char frchaine[TAILLE_MAX] = ""; //frchaine vide de TAILLE_MAX
    if (frfichier != NULL)
    {
        while (fgets(frchaine, TAILLE_MAX, frfichier) != NULL) // On lit le frfichier tant qu'on ne reçoit pas d'erreur (NULL) donc tant qu'on arrive pas à la fin

        {
            printf("%s", frchaine); // On affiche la chaîne qu'on vient de lire
        }
    }
}

int fr_menus(int *frchoix, FILE *frfichier)//l'utilisateur choisi entre les différentes options
{
    int y = 0;
    int a = 0;
    int *frpa = &a; //pa pointe sur l'adresse de a
    int b = 0;
    int *frpro = &b;
    int c = 0;
    int *frca = &c;
    int d = 0;
    int *frpl = &d;
    int e = 0;
    int *frpf = &e; 

    //system("clear");
    switch(*frchoix)
    {
        case 1 : //Si 1 alors afficher menu 1
        fclose(frfichier);
        frfichier = fopen("MenusFR/menu1fr", "r");
        fr_debut(frfichier);
        scanf("%d", &a);//choix 1
        fflush(stdin);
        frprocessus(frpa, frfichier);
        break;

        case 2 : //Si 2 alors afficher menu 2
        fclose(frfichier);
        frfichier = fopen("MenusFR/menu2fr", "r");
        fr_debut(frfichier);        
        scanf("%d", &b);//choix 2
        fflush(stdin);
        frprogrammes(frpro, frfichier);
        break;

        case 3 : //Si 3 alors afficher menu 3
        fclose(frfichier);
        frfichier = fopen("MenusFR/menu3fr", "r");
        fr_debut(frfichier);
        scanf("%d", &c);
        fflush(stdin);//choix 3
        fr_azerty(frca, frfichier);
        break;

        case 4 : //Si 4 alors afficher menu 4
        fclose(frfichier);
        frfichier = fopen("MenusFR/menu4fr", "r");
        fr_debut(frfichier);
        scanf("%d", &d); //choix 4
        fflush(stdin);
        frperiph(frpl, frfichier);
        break;

        case 5 : //Si 5 alors afficher menu 5
        fclose(frfichier);
        frfichier = fopen("MenusFR/menu5fr", "r");
        fr_debut(frfichier);
        scanf("%d", &e); //choix 5
        fflush(stdin);
        fr_file(frpf, frfichier);
        break;

        default : //équivalent du else, facultatif mais on le laisse pour un soucis de cohérence
        printf("\nErreur\n");
        fr_menus(&y,frfichier);
        break;
    }
    return 0;
}



int assist_fr(int argc, char *argv[])
{
    system("clear");//on fait un clear au démarrage
    int frchoix = 0;
    FILE *frfichier = NULL;
    frfichier = fopen("MenusFR/menu0fr", "r"); //Dans le main pour etre affiché en premier
    fr_debut(frfichier); //pour afficher le frfichier
    scanf("%d", &frchoix); //Pour demander le choix du menu
    system("clear");
    fr_menus(&frchoix, frfichier);

    return 1;
}

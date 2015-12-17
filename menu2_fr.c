#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu2_fr.h"
#include "assist_fr.h"

int frinstall()
{
	char frs1[80]="sudo apt-get install "; //taille des 2 char
    char frs2[50]=""; //nb de caractères du programme
    
    printf("Veuillez entrer le nom du programme que vous voulez installer:\n");
    scanf("%s",frs2);
    strcat(frs1,frs2);
    system(frs1);
    fflush(stdin); //vider le buffer

    return 0;
}

int frrmove()
{
	char frs3[80]="sudo apt-get remove "; //taille des 2 char
    char frs4[50]=""; //nb de caractères du programme
    
    printf("Veuillez entrer le nom du programme que vous voulez désinstaller:\n");
    scanf("%s",frs4);    
    strcat(frs3,frs4);
    system(frs3);
    fflush(stdin); //vider le buffer

    return 0;
}

int frprogrammes(int *frpro, FILE *frfichier)
{
    int frchoix = 0;
    int y = 2;
	switch(*frpro)
	{
		case 1 :
		frinstall(); //appel fonction install
        fr_menus(&y,frfichier);
		break;

		case 2 :
		frrmove(); //appel fonction rmove
        fr_menus(&y,frfichier);
		break;

        case 3 :
        fclose(frfichier);
        system("clear");
        frfichier = fopen("menu0", "r"); 
        fr_debut(frfichier);
        scanf("%d", &frchoix);
        fr_menus(&frchoix, frfichier);
        break;

		default :
		puts("\nErreur\n"); //=else(error)
        fr_menus(&y,frfichier);
		break;
	}
	return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu2_en.h"
#include "assist_en.h"

int install()
{
	char s1[80]="sudo apt-get install "; //taille des 2 char
    char s2[50]=""; //nb de caractères du programme
    
    printf("Please enter the program name you want to install:\n");
    scanf("%s",s2);
    strcat(s1,s2);
    system(s1);
    fflush(stdin); //vider le buffer

    return 0;
}

int rmove()
{
	char s3[80]="sudo apt-get remove "; //taille des 2 char
    char s4[50]=""; //nb de caractères du programme
    
    printf("Please enter the program name you want to uninstall:\n");
    scanf("%s",s4);    
    strcat(s3,s4);
    system(s3);
    fflush(stdin); //vider le buffer

    return 0;
}

int programmes(int *pro, FILE *fichier)
{
    int choix = 0;
    int i = 2;
	switch(*pro)
	{
		case 1 :
		install(); //appel fonction install
        my_menus(&i,fichier);
		break;

		case 2 :
		rmove(); //appel fonction rmove
        my_menus(&i,fichier);
		break;

        case 3 :
        fclose(fichier);
        system("clear");
        fichier = fopen("menu0", "r"); 
        my_debut(fichier);
        scanf("%d", &choix);
        my_menus(&choix, fichier);
        my_menus(&i,fichier);
        break;

		case 4 :
		puts("\nError\n"); //=else(error)
		break;
	}
	return 0;
}
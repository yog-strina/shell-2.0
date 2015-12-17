#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu5_en.h"
#include "assist_en.h"
 
int my_create() // = mkdir
{
    char s21[80]="mkdir "; //taille des 2 char
    char s22[50]=""; //nb de caractères du nom
    
    printf("\nPlease enter the folder name you want to create with his acces path :\n");
    scanf("%s",s22);
    strcat(s21,s22);
    system(s21);
    fflush(stdin);

    return 0;
}

int my_suppr() // = rm
{
    char s23[80]="rm -Rf "; //taille des 2 char
    char s24[50]=""; //nb de caractères du nom
    
    printf("\nPlease enter the folder name do you want to delete with his acces path :\n");
    scanf("%s",s24);
    strcat(s23,s24);
    system(s23);
    fflush(stdin);

    return 0;
}

int my_nano() // = nano
{
    char s25[80]="nano "; //taille des 2 char
    char s26[50]=""; //nb de caractères du nom
    
    printf("\nPlease enter the file name you want to open with his acces path :\n");
    scanf("%s",s26);
    strcat(s25,s26);
    system(s25);
    fflush(stdin);

    return 0;
}

int my_touch() // = touch
{
	char s27[80]="touch "; //taille des 2 char
    char s28[50]=""; //nb de caractères du nom
    
    printf("\nPlease enter the file name you want to create with his acces path :\n");
    scanf("%s",s28);
    strcat(s27,s28);
    system(s27);
    fflush(stdin);

    return 0;
}

int my_rm() // =rm
{
	char s29[80]="rm "; //taille des 2 charPlease enter the folder name do you want to create with his acces path :
    char s30[50]=""; //nb de caractères du nom
    
    printf("\nPlease enter the file name you want to delete with his acces path :\n");
    scanf("%s",s30);
    strcat(s29,s30);
    system(s29);
    fflush(stdin);

    return 0;
}

int my_ls() // =ls
{
    char s31[80]="ls -l --color "; //taille des 2 char
    char s32[50]=""; //nb de caractères du nom
    
    printf("\nPlease enter the folder name do you want to list with his acces path : : \n");
    scanf("%s",s32);
    strcat(s31,s32);
    system(s31);
    fflush(stdin);

    return 0;
}

int my_file(int *pf, FILE *fichier)
{
	int choix = 0;
    int i = 5;
	switch(*pf)
	{
		case 1 :
        my_ls();
        my_menus(&i,fichier);
		break;

		case 2 :
		my_create();
        my_menus(&i,fichier);
		break;

		case 3 :
		my_suppr();
        my_menus(&i,fichier);
		break;

		case 4 :
		my_nano();
        my_menus(&i,fichier);
		break;

		case 5 :
		my_touch();
        my_menus(&i,fichier);
		break;

		case 6 :
		my_rm();
        my_menus(&i,fichier);
		break;

		case 7 :
		fclose(fichier);
		system("clear");
		fichier = fopen("menu0", "r"); //Dans le main pour etre affiché en premier
    	my_debut(fichier); //pour afficher le 
    	scanf("%d", &choix);
    	my_menus(&choix, fichier);
		break;

		default : 
		printf("Error\n");
        my_menus(&i,fichier);
		break;
	}
	return 0;
}
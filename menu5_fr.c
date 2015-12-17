#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu5_fr.h"
#include "assist_fr.h"
 
int fr_create() // = mkdir
{
    char frs21[80]="mkdir "; //taille des 2 char
    char frs22[50]=""; //nb de caractères du nom
    
    printf("\nVeuillez entrer le nom du répertoire que vous voulez créer avec son chemin \nd'accès :\n");
    scanf("%s",frs22);
    strcat(frs21,frs22);
    system(frs21);
    fflush(stdin);

    return 0;
}

int fr_suppr() // = rm
{
    char frs23[80]="rm -Rf "; //taille des 2 char
    char frs24[50]=""; //nb de caractères du nom
    
    printf("\nVeuillez entrer le nom du répertoire que vous voulez supprimer avec son chemin \nd'accès :\n");
    scanf("%s",frs24);
    strcat(frs23,frs24);
    system(frs23);
    fflush(stdin);

    return 0;
}

int fr_nano() // = nano
{
    char frs25[80]="nano "; //taille des 2 char
    char frs26[50]=""; //nb de caractères du nom
    
    printf("\nVeuillez entrer le nom du frfichier que vous voulez ouvrir avec son chemin \nd'accès :\n");
    scanf("%s",frs26);
    strcat(frs25,frs26);
    system(frs25);
    fflush(stdin);

    return 0;
}

int fr_touch() // = touch
{
	char frs27[80]="touch "; //taille des 2 char
    char frs28[50]=""; //nb de caractères du nom
    
    printf("\nVeuillez entrer le nom du frfichier que vous voulez créer avec son chemin \nd'accès :\n");
    scanf("%s",frs28);
    strcat(frs27,frs28);
    system(frs27);
    fflush(stdin);

    return 0;
}

int fr_rm() // =rm
{
	char frs29[80]="rm "; //taille des 2 char
    char frs30[50]=""; //nb de caractères du nom
    
    printf("\nVeuillez entrer le nom du frfichier que vous voulez supprimer avec son chemin \nd'accès :\n");
    scanf("%s",frs30);
    strcat(frs29,frs30);
    system(frs29);
    fflush(stdin);

    return 0;
}

int fr_ls() // =ls
{
    char frs31[80]="ls -l --color "; //taille des 2 char
    char frs32[50]=""; //nb de caractères du nom
    
    printf("\nVeuillez entrer le nom du répertoire à lister avec son chemin \nd'accès : \n");
    scanf("%s",frs32);
    strcat(frs31,frs32);
    system(frs31);
    fflush(stdin);

    return 0;
}

int fr_file(int *frpf, FILE *frfichier)
{
    int y = 5;
	int frchoix = 0;
	switch(*frpf)
	{
		case 1 :
        fr_ls();
        fr_menus(&y,frfichier);
		break;

		case 2 :
		fr_create();
        fr_menus(&y,frfichier);
		break;

		case 3 :
		fr_suppr();
        fr_menus(&y,frfichier);
		break;

		case 4 :
		fr_nano();
        fr_menus(&y,frfichier);
		break;

		case 5 :
		fr_touch();
        fr_menus(&y,frfichier);
		break;

		case 6 :
		fr_rm();
        fr_menus(&y,frfichier);
		break;

		case 7 :
		fclose(frfichier);
		system("clear");
		frfichier = fopen("menu0", "r"); //Dans le main pour etre affiché en premier
    	fr_debut(frfichier); //pour afficher le 
    	scanf("%d", &frchoix);
    	fr_menus(&frchoix, frfichier);
		break;

		default : 
		printf("Erreur\n");
        fr_menus(&y,frfichier);
		break;
	}
	return 0;
}
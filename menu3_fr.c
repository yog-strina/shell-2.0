#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu3_fr.h"
#include "assist_fr.h"

int fr_x()
{
    char frs10[80]="su ";
    char frs11[50]="";
    
    printf("\nVeuillez saisir le nom de l'utilisateur : ");
    scanf("%s",frs11);
    strcat(frs10,frs11);
    system(frs10);
    fflush(stdin);

    return 0;
}

int fr_addUser()
{
    char frs13[80]="sudo adduser ";
    char frs14[50]="";
    
    printf("\nVeuillez saisir le nom de l'utilisateur à ajouter : ");
    scanf("%s",frs14);
    strcat(frs13,frs14);
    system(frs13);
    fflush(stdin);

    return 0;
}

int fr_delUser()
{
    char frs15[80]="sudo deluser ";
    char frs16[50]="";
    
    printf("\nVeuillez saisir le nom de l'utilisateur à supprimer : ");
    scanf("%s",frs16);
    strcat(frs15,frs16);
    system(frs15);
    fflush(stdin);

    return 0;
}

int fr_azerty(int *frca, FILE *frfichier)
{
    int frchoix = 0;
    int y = 3;
	switch(*frca)
	{
		case 1 :
		system("awk -F: '$0=$1' /etc/passwd");
        fr_menus(&y,frfichier);
		break;

		case 2 :
		fr_x();
        fr_menus(&y,frfichier);
		break;

		case 3 :
		system("su");
        fr_menus(&y,frfichier);
		break;

		case 4 :
		fr_addUser();
        fr_menus(&y,frfichier);
		break;

		case 5 : 
		fr_delUser();
        fr_menus(&y,frfichier);
		break;

        case 6 :
        fclose(frfichier);
        system("clear");
        frfichier = fopen("menu0", "r"); 
        fr_debut(frfichier);
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
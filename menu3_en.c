#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu3_en.h"
#include "assist_en.h"

int my_x()
{
    char s10[80]="su ";
    char s11[50]="";
    
    printf("\nPlease enter the username you want to connect with : \n");
    scanf("%s",s11);
    strcat(s10,s11);
    system(s10);
    fflush(stdin);

    return 0;
}

int my_addUser()
{
    char s13[80]="sudo adduser ";
    char s14[50]="";
    
    printf("\nPlease enter the username you want to create : \n");
    scanf("%s",s14);
    strcat(s13,s14);
    system(s13);
    fflush(stdin);

    return 0;
}

int my_delUser()
{
    char s15[80]="sudo deluser ";
    char s16[50]="";
    
    printf("\nPlease enter the username you want to delete : \n");
    scanf("%s",s16);
    strcat(s15,s16);
    system(s15);
    fflush(stdin);

    return 0;
}

int my_azerty(int *ca, FILE *fichier)
{
    int choix = 0;
    int i = 3;
	switch(*ca)
	{
		case 1 :
		system("awk -F: '$0=$1' /etc/passwd");
        my_menus(&i,fichier);
		break;

		case 2 :
		my_x();
        my_menus(&i,fichier);
		break;

		case 3 :
		system("su");
        my_menus(&i,fichier);
		break;

		case 4 :
		my_addUser();
        my_menus(&i,fichier);
		break;

		case 5 : 
		my_delUser();
        my_menus(&i,fichier);
		break;

        case 6 :
        fclose(fichier);
        system("clear");
        fichier = fopen("menu0", "r"); 
        my_debut(fichier);
        scanf("%d", &choix);
        my_menus(&choix, fichier);
        my_menus(&i,fichier);
        break;

		default : 
		printf("Error\n");
        my_menus(&i,fichier);
		break;
	}
    return 0;
}
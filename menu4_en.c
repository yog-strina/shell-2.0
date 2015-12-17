#include <stdlib.h>
#include <stdio.h>
#include "menu4_en.h"
#include "assist_en.h"

int periph(int *pl, FILE *fichier)
{
	int choix = 0;
	int i = 4;
	switch(*pl)
	{
		case 1 :
		system("lsusb");
		my_menus(&i,fichier);
		break;

		case 2 :
		system("lspci");
		my_menus(&i,fichier);
		break;

		case 3 :
		fclose(fichier);
		fichier = fopen("menu0", "r"); //Dans le main pour etre affiché en premier
	    my_debut(fichier); //pour afficher le 
	    scanf("%d", &choix);
	    my_menus(&choix, fichier);
		break;

		default :
		printf("\nError\n");
		my_menus(&i,fichier);
		break;
	}
	return 0;
}
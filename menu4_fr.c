#include <stdlib.h>
#include <stdio.h>
#include "menu4_fr.h"
#include "assist_fr.h"

int frperiph(int *frpl, FILE *frfichier)
{
	int frchoix = 0;
	int y = 4;
	switch(*frpl)
	{
		case 1 :
		system("lsusb");
		fr_menus(&y,frfichier);
		break;

		case 2 :
		system("lspci");
		fr_menus(&y,frfichier);
		break;

		case 3 :
		fclose(frfichier);
		frfichier = fopen("menu0", "r"); //Dans le main pour etre affiché en premier
	    fr_debut(frfichier); //pour afficher le 
	    scanf("%d", &frchoix);
	    fr_menus(&frchoix, frfichier);
		break;

		default :
		printf("\nErreur\n");
		fr_menus(&y,frfichier);
		break;
	}
	return 0;
}
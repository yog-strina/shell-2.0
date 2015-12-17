#include <stdlib.h>
#include <stdio.h>
#include <string.h> //pour strcat
#include "menu1_fr.h"
#include "assist_fr.h"

int frpid()
{
    char frs1[20]="kill "; //taille des 2 char
    char frs2[10]=""; //nb de caractères des PID 
    
    printf("\nVeuillez entrer le PID du processus à arrêter parmis les processus ci-dessus:\n");
    scanf("%s",frs2);
    strcat(frs1,frs2);
    system(frs1);
    fflush(stdin);

    return 0;
}

int frprocessus(int *frpa, FILE *frfichier)
{

	int frchoix = 0;
	int y = 1;
	switch(*frpa)
	{
		case 1 : //Si 1 affiche la commande ps -u
		system("ps -u");
		fr_menus(&y,frfichier);
		break;

		case 2 : //Si 2 affiche la commande ps aux
		system("ps aux");
		fr_menus(&y,frfichier);

		break;

		case 3 : //Si 3 affiche la commande ps puis fait un concaténation de chaines de caractères (printf ne focntionne pas dans la fonction system)
		system("ps"); 
		frpid();
		fr_menus(&y,frfichier);
		break;

		case 4 :
		fclose(frfichier);
		system("clear");
		frfichier = fopen("menu0", "r"); 
    	fr_debut(frfichier);
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

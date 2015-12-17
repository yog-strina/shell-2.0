#include <stdlib.h>
#include <stdio.h>
#include <string.h> //pour strcat
#include "menu1_en.h"
#include "assist_en.h"

int pid()
{
    char s1[20]="kill "; //taille des 2 char
    char s2[10]=""; //nb de caractères des PID 
    
    printf("\nEnter the PID of the process to kill\n");
    scanf("%s",s2);
    strcat(s1,s2);
    system(s1);
    fflush(stdin);

    return 0;
}

int processus(int *pa, FILE *fichier)
{
	int i = 1;
	int choix = 0;
	switch(*pa)
	{
		case 1 : //Si 1 affiche la commande ps -u
		system("ps -u");
		my_menus(&i,fichier);
		break;

		case 2 : //Si 2 affiche la commande ps aux
		system("ps aux");
		my_menus(&i,fichier);
		break;

		case 3 : //Si 3 affiche la commande ps puis fait un concaténation de chaines de caractères (printf ne focntionne pas dans la fonction system)
		system("ps"); 
		pid();
		my_menus(&i,fichier);
		break;
		
		case 4 :
		fclose(fichier);
		system("clear");
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

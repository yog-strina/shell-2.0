#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 1000 // Tableau de taille 1000
int main(int argc, char *argv[])
{
  FILE* fichier = NULL;
  int param[2] = {0}; // Tableau des 2 paramètres.
  fichier = fopen("settings.config", "r"); // ouverture du fichier config




  if (fichier != NULL) // on vérifie si le fichier à pu etre ouvert
    {
      fscanf(fichier, "%d", &param[0]); // on récupère le paramètre mode
      fseek(fichier, 72, SEEK_CUR); // Se positioner à la ligne par rapport au txt
      fscanf(fichier, "%d", &param[1]); // on récupère le paramètre langage


      
      switch(param[0]) // On dit quel à été le mode choisi dans le fichier config
	{
	case 1:
	  natural_shell(param[1]);
	  break;
	case 2:
	  if (param[1] == 1)
	    assist_en();
	  break;
	case 3:
	  expert_shell();
	  break;
	default:
	  printf("choix inconnu\n");
	  break;
	}

      fclose(fichier); // on referme le fichier pour libérer de la mémoire.
    }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int expert_shell()
{
    char cmd[250], path[256]; //allocation de environ 250 caractères (suffisant pour environ 3 lignes de commandes)
    char cmd1[] = "cd\n", cmd2[] = "chdir\n";
    //char hour[] = {system("date")};
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);




    FILE* fichier = NULL;
    fichier = fopen("historique.log", "a"); // ouverture du fichier contenant l'historique des commandes.
    fprintf(fichier, "\n%d-%d-%d %d:%d:%d ---------------------------------------------------\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);//ecriture dans le fichier historique
    fclose(fichier); //on referme le fichier


while(1) //boucle placeholder d'entrée des commandes
{
    fichier = fopen("historique.log", "a"); // ouverture du fichier contenant l'historique des commandes.



    if (fichier != NULL)
    {
        printf("Entrez votre commande ci dessous:\n"); //placeholder du shell
        fgets(cmd, sizeof cmd, stdin); //equivalent de l'entrée de la commande.
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(fichier, "%d:%d:%d %s",  tm.tm_hour, tm.tm_min, tm.tm_sec, cmd); //ecriture dans le fichier historique
	if (strcmp(cmd, "hanoi") == 0 || strcmp(cmd, "hanoi\n") == 0)
	  hanoi_towers();
	else
	  system(cmd);
    }

    fclose(fichier); //on referme le fichier

fflush(stdin); //on libère le buffer pour eviter une erreur}

}
   return 0;
}

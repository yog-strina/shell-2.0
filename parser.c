#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>


 struct    command
    {
    char    **cmd;
    char    **keyWords;
    };

struct command listecommandesnaturel;


char *cleanstring(char *chainedecaractere)

{
/* Si le dernier caractère de la chaine de caractère est \n, on supprime le dernier caractère de la chaine */
    if ((strlen(chainedecaractere)>0) && (chainedecaractere[strlen (chainedecaractere) - 1] == '\n'))
            chainedecaractere[strlen (chainedecaractere) - 1] = '\0';


    return chainedecaractere;





}

char *replace_str(char *str, char *orig, char *rep)
{
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
    return str;

  strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  return buffer;
}



int compterlignes(char *lang)

{
    DIR*    FD;
    struct  dirent* in_file;
    FILE    *entry_file;
    char    cwd[1024];
    char    buffer[BUFSIZ];
    int     m = 0;
    char    *nomfichier=NULL;
    int     i = 1;
    char    dossierdictionnaires[50] = "";








    /* On relève le repertoire dans lequel on travaille et on le stocke dans la variable cwd*/
    if (getcwd(cwd, sizeof(cwd)) == NULL)

   {
    perror("getcwd() error");
    return 1;
    }

/* Si la fonction est lancée en mode français, alors le dossier contenant les dictionnaires est dictionnaires/  */
    if(strcmp(lang,"fr") == 0 )
    {
    strcpy(dossierdictionnaires,"dictionnaires/");
    strcat(cwd, "/dictionnaires/");

    }

/* Si la fonction est lancée en mode anglais, alors le dossier contenant les dictionnaires est dictionnaires_en/  */

    else if (strcmp(lang,"en") == 0)

    {
    strcpy(dossierdictionnaires,"dictionnaires_en/");
    strcat(cwd, "/dictionnaires_en/");

    }



    /* On scanne les fichiers contenus dans le répretoire dictionnaires/ */
    if (NULL == (FD = opendir (cwd)))
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));

        return 1;
    }
    while ((in_file = readdir(FD)))
    {
        /* Etant donné que sous linux, les répertoires sont des fichiers, on vérifie que le fichier en question n'est pas un répertoire */

        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))
            continue;




        /* On ouvre chaque fichier contenu dans le répertoire dictionnaires/ */
        entry_file = fopen(strcat(dossierdictionnaires, in_file->d_name), "r");

        if (entry_file == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));

            return 1;
        }

        /* On met le contenu de chaque fichier dans un buffer */
        while (fgets(buffer, BUFSIZ, entry_file) != NULL)

        {

            /* On réinitialise la variable i lorsqu'on change de fichier */
            if (nomfichier != NULL && strcmp(in_file->d_name,nomfichier) != 0)
            {

            i = 1;


            }

            /*  Si on passe à un nouveau fichier, alors on décrémente la variable m qui contient le nombre de lignes */
            if (i == 1)

            {

            m--;
            }



            nomfichier = strdup(in_file->d_name);

            i++;
            m++;



        }

        /* On ferme le fichier avant d'ouvrir le prochain */

        fclose(entry_file);

        if(strcmp(lang,"fr") == 0 )
        {
            strcpy (dossierdictionnaires, "dictionnaires/");

        }

        else if (strcmp(lang,"en") == 0)

        {
            strcpy (dossierdictionnaires, "dictionnaires_en/");

        }


    }

    closedir(FD);
    free(in_file);
    free(nomfichier);

    /* On renvoie le nombre de lignes total (en excluant les commandes) contenu dans les dictionnaires */

    return m;
}










/* This is just a sample code, modify it to meet your need */
int initialiserdictionnaires(int nombrelignes,char *lang)
{
    DIR*    FD;
    struct  dirent* in_file;
    FILE    *entry_file;
    char    cwd[1024];
    char    buffer[BUFSIZ];
    char    *nomfichier=NULL;
    int     i = 1;
    char    *commande=NULL;
    int     p = 0;
    char    dossierdictionnaires[50] = "";


    /* On alloue la mémoire nécessaire à notre tableau en 2 dimensions */

    listecommandesnaturel.keyWords = calloc(nombrelignes, sizeof(char*));

    listecommandesnaturel.cmd = calloc(nombrelignes, sizeof(char*));






    /* On relève le repertoire dans lequel on travaille et on le stocke dans la variable cwd*/

    if (getcwd(cwd, sizeof(cwd)) == NULL)

   {
    perror("getcwd() error");
    return 1;
    }

/* Si la fonction est lancée en mode français, alors le dossier contenant les dictionnaires est dictionnaires/  */
    if(strcmp(lang,"fr") == 0 )
    {
        strcpy(dossierdictionnaires,"dictionnaires/");
        strcat(cwd, "/dictionnaires/");

    }
/* Si la fonction est lancée en mode anglais, alors le dossier contenant les dictionnaires est dictionnaires_en/  */

    else if (strcmp(lang,"en") == 0)

    {
        strcpy(dossierdictionnaires,"dictionnaires_en/");
        strcat(cwd, "/dictionnaires_en/");

    }



    /* On scanne les fichiers contenus dans le répretoire dictionnaires/ */
    if (NULL == (FD = opendir (cwd)))
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));

        return 1;
    }
    while ((in_file = readdir(FD)))
    {
        /* Etant donné que sous linux, les répertoires sont des fichiers, on vérifie que le fichier en question n'est pas un répertoire */

        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))
            continue;




        /* On ouvre chaque fichier contenu dans le répertoire dictionnaires/ */

        entry_file = fopen(strcat(dossierdictionnaires, in_file->d_name), "r");

        if (entry_file == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));

            return 1;
        }


        /* On met le contenu de chaque fichier dans un buffer */

        while (fgets(buffer, BUFSIZ, entry_file) != NULL)
        {


            /* On réinitialise la variable i lorsqu'on change de fichier */

            if (nomfichier != NULL && strcmp(in_file->d_name,nomfichier) != 0)
            {

                i = 1;

            }


            /*  Si on passe à un nouveau fichier, alors la première ligne est la commande à exécuter et on la stocke */

            if (i == 1)

            {

                commande = strdup(buffer);


            }

            /* Si on est pas à la première ligne d'un fichier, alors on remplit le tableau jusqu'à sa limite */

            else if ( p < nombrelignes )

            {

                listecommandesnaturel.cmd[p] = strdup(commande);

                listecommandesnaturel.keyWords[p] = strdup(buffer);

                p++;

            }

            nomfichier = strdup(in_file->d_name);

            i++;


        }

        /* On ferme le fichier avant d'ouvrir le prochain */
        fclose(entry_file);


        if(strcmp(lang,"fr") == 0 )
        {
            strcpy (dossierdictionnaires, "dictionnaires/");

        }

        else if (strcmp(lang,"en") == 0)

        {
            strcpy (dossierdictionnaires, "dictionnaires_en/");

        }





    }

    closedir(FD);
    free(in_file);
    free(nomfichier);
    free(commande);


    return 0;
}

int modenaturel(int nombrelignes,char *lang)

{
    int     i=0;
    int     p;
    int     q=0;
    char    *keyword=NULL;
    char    *cmd=NULL;
    char    *entreetronquee=NULL;
    char    *entree=NULL;

    /* On alloue 256 caractères à la variable qui stockera l'entrée de l'utilisateur */

    entree = calloc(256, sizeof(char));

    /* Si la fonction est lancée en mode français, alors on affiche un message en français  */

    if(strcmp(lang,"fr") == 0 )
    {

    printf ("Que souhaitez-vous faire maintenant ?\n");

    }

    /* Si la fonction est lancée en mode anglais, alors on affiche un message en anglais  */

    else if (strcmp(lang,"en") == 0)

    {

    printf ("What do you want to do now ?\n");


    }



    fgets (entree, 256, stdin);

    /* On retire le caractère \n de l'entrée de l'utilisateur */
    entree = strdup(cleanstring(entree));

    /* Tant que on a pas atteint la fin du tableau et qu'on a pas trouvé ce qu'on cherchait */

    while (i < nombrelignes && q == 0 )

    {

        keyword = strdup(listecommandesnaturel.keyWords[i]);
        keyword = strdup(cleanstring(keyword));

        /* On stocke la longueur du mot-clé dans la variable p */

        p = strlen(keyword);

        /* On prend les p premiers caractères de l'entrée de l'utilisateur */

        entreetronquee = strndup(entree,p);

        /* Si la longueur de la commande ne fait qu'un caractère et que le mot-clé est dans l'entrée de l'utilisateur alors on le supprime */

        if (strlen(listecommandesnaturel.cmd[i]) == 1 && strstr(entree,keyword) != 0 )
        {

        entree = strdup(replace_str(entree,keyword,""));

        }

        /* Si l'entrée tronquée est égale au mot-clé alors on remplace l'entrée tronquée par la commande correspondante */

        if (strcmp(entreetronquee,keyword) == 0 && strlen(listecommandesnaturel.cmd[i]) > 1 && strlen(listecommandesnaturel.keyWords[i]) > 1 )

        {
        q = 1;
        cmd = strdup(replace_str(entree,keyword,cleanstring(listecommandesnaturel.cmd[i])));

            if (strstr(cmd,"exit") != 0)
            {
            free(entree);
            free(listecommandesnaturel.keyWords);
            free(listecommandesnaturel.cmd);
            free(keyword);
            free(cmd);
            free(entreetronquee);
            exit(0);

            }

            else
            {

            system(cmd);

            free(entree);
            free(keyword);
            free(cmd);
            free(entreetronquee);

            modenaturel(nombrelignes,lang);

            }

        }

        /* Si on a atteint la fin du tableau et qu'on a rien trouvé alors on rappelle la fonction */

        if (i == (nombrelignes - 1))
        {

        if(strcmp(lang,"fr") == 0 )
        {

        printf("Entrée introuvable, veuillez reformulez votre demande.\n");

        }

        else if (strcmp(lang,"en") == 0)

        {

        printf ("We cannot satisfy your demand. Please rephrase your request ?\n");


        }




        free(entree);
        free(keyword);
        free(cmd);
        free(entreetronquee);

        modenaturel(nombrelignes,lang);
        }
        i++;






    }





    free(entree);
    free(listecommandesnaturel.keyWords);
    free(listecommandesnaturel.cmd);
    free(keyword);
    free(cmd);
    free(entreetronquee);

    return 0;


}

int natural_shell(int flag)

{
  int    nombrelignes;
  char	*lang;

  lang = "en";
  if (flag == 2)
    lang = "fr";
  nombrelignes = compterlignes(lang);

  initialiserdictionnaires(nombrelignes, lang);

  modenaturel(nombrelignes,lang);

  return 0;
}

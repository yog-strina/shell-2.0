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



int compterlignes()

{
    DIR*    FD;
    struct  dirent* in_file;
    FILE    *entry_file;
    char    cwd[1024];
    char    dossierdictionnaires[50] = "dictionnaires/";
    char    buffer[BUFSIZ];
    int     m = 0;
    char    *nomfichier=NULL;
    int     i = 1;
    char    *commande=NULL;








    if (getcwd(cwd, sizeof(cwd)) != NULL)

    {
    fprintf(stdout, "Current working dir: %s\n", cwd);
    }

    else

   {
    perror("getcwd() error");
    return 1;
    }



    /* Scanning the in directory */
    if (NULL == (FD = opendir (strcat(cwd, "/dictionnaires/"))))
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));

        return 1;
    }
    while ((in_file = readdir(FD)))
    {
        /* On linux/Unix we don't want current and parent directories
         * On windows machine too, thanks Greg Hewgill
         */
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))
            continue;




        /* Open directory entry file for common operation */
        /* TODO : change permissions to meet your need! */
        entry_file = fopen(strcat(dossierdictionnaires, in_file->d_name), "r");

        if (entry_file == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));

            return 1;
        }


        while (fgets(buffer, BUFSIZ, entry_file) != NULL)

        {

            if (nomfichier != NULL && strcmp(in_file->d_name,nomfichier) != 0)
            {

            i = 1;
            printf ("Nouveau fichier\n");


            }


            if (i == 1)

            {
            commande = strdup(buffer);

            printf("%s\n", commande);

            m--;
            }

            else

            {



            }

            nomfichier = strdup(in_file->d_name);

            i++;
            m++;



        }


        fclose(entry_file);

        strcpy (dossierdictionnaires, "dictionnaires/");
    }


    m--;

    //printf("%d\n",m);

    /* Don't forget to close common file before leaving */

    return m;
}










/* This is just a sample code, modify it to meet your need */
int initialiserdictionnaires(int nombrelignes)
{
    DIR*    FD;
    struct  dirent* in_file;
    FILE    *entry_file;
    char    cwd[1024];
    char    dossierdictionnaires[50] = "dictionnaires/";
    char    buffer[BUFSIZ];
    char    *nomfichier=NULL;
    int     i = 1;
    char    *commande=NULL;
    int     p = 0;
    char    *longueur=NULL;

    listecommandesnaturel.keyWords = calloc(nombrelignes, sizeof(char*));

    listecommandesnaturel.cmd = calloc(nombrelignes, sizeof(char*));








    if (getcwd(cwd, sizeof(cwd)) != NULL)

    {
    fprintf(stdout, "Current working dir: %s\n", cwd);
    }

    else

   {
    perror("getcwd() error");
    return 1;
    }



    /* Scanning the in directory */
    if (NULL == (FD = opendir (strcat(cwd, "/dictionnaires/"))))
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));

        return 1;
    }
    while ((in_file = readdir(FD)))
    {
        /* On linux/Unix we don't want current and parent directories
         * On windows machine too, thanks Greg Hewgill
         */
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))
            continue;




        /* Open directory entry file for common operation */
        /* TODO : change permissions to meet your need! */
        entry_file = fopen(strcat(dossierdictionnaires, in_file->d_name), "r");

        if (entry_file == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));

            return 1;
        }

   //     listecommandesnaturel.keyWords = malloc(nombrelignes * sizeof(char*));

   //     listecommandesnaturel.cmd = malloc(nombrelignes * sizeof(char*));









        while (fgets(buffer, BUFSIZ, entry_file) != NULL)
        {




            if (nomfichier != NULL && strcmp(in_file->d_name,nomfichier) != 0)
            {

            i = 1;
            printf ("Nouveau fichier\n");


            }


                if (i == 1)

                {
                commande = strdup(buffer);

                printf("%s\n", commande);


                }

                else if (p < nombrelignes)

                {

                longueur = strdup(buffer);
                printf("%ld\n", sizeof(longueur));

                listecommandesnaturel.cmd[p] = strdup(commande);

                listecommandesnaturel.keyWords[p] = strdup(buffer);

                p++;

                }

            nomfichier = strdup(in_file->d_name);

            //printf ("%s\n", buffer);

            i++;










        }

        //printf("%s\n", listecommandesnaturel.keyWords[0]);









        fclose(entry_file);



        strcpy (dossierdictionnaires, "dictionnaires/");
    }

    printf("Première ligne : %s\n", listecommandesnaturel.cmd[0]);
    printf("Première ligne : %s\n", listecommandesnaturel.keyWords[0]);

    /* Don't forget to close common file before leaving */

    return 0;
}

int modeexpert(int nombrelignes)

{
    int     i=0;
    int     p;
    char    *keyword=NULL;
    char    *cmd=NULL;
    char    *entreetronquee=NULL;
    /* Allocate memory and check if okay. */
    char    *entree=NULL;


    entree = calloc(256, sizeof(char));
    printf ("Que souhaitez-vous faire maintenant ?\n");
    fgets (entree, 256, stdin);
    entree = strdup(cleanstring(entree));

    printf("%s\n", entree);

    while (i < nombrelignes)

    {

        keyword = strdup(listecommandesnaturel.keyWords[i]);
        keyword = strdup(cleanstring(keyword));

        p = strlen(keyword);



        entreetronquee = strndup(entree,p);


        if (strcmp(entreetronquee,keyword) == 0)

        {

        printf("Commande trouvée\n");
        cmd = strdup(replace_str(entree,keyword,cleanstring(listecommandesnaturel.cmd[i])));
        printf("%s", cmd);

        }
        i++;



    }






    free(entree);
    free(listecommandesnaturel.keyWords);
    free(listecommandesnaturel.cmd);




}

int main()

{
int    nombrelignes;

nombrelignes = compterlignes();

initialiserdictionnaires(nombrelignes);

modeexpert(nombrelignes);

//liredictionnaires(compterlignes());

return 0;
}

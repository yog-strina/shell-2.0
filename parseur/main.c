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

    /* Don't forget to close common file before leaving */

    return m;
}










/* This is just a sample code, modify it to meet your need */
int liredictionnaires(int nombrelignes)
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

        listecommandesnaturel.keyWords = malloc(nombrelignes * sizeof(char*));

        listecommandesnaturel.cmd = malloc(nombrelignes * sizeof(char*));






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

            p--;
            }

            else

            {

            listecommandesnaturel.cmd[p] = strdup(commande);

            listecommandesnaturel.keyWords[p] = strdup(buffer);



            }

            nomfichier = strdup(in_file->d_name);

            //printf ("%s\n", buffer);

            i++;

            p++;






        }

        //printf("%s\n", listecommandesnaturel.keyWords[0]);









        fclose(entry_file);



        strcpy (dossierdictionnaires, "dictionnaires/");
    }

    printf("Première ligne : %s\n", listecommandesnaturel.cmd[0]);
    printf("Première ligne : %s\n", listecommandesnaturel.keyWords[0]);

    /* Don't forget to close common file before leaving */
    free(listecommandesnaturel.keyWords);
    free(listecommandesnaturel.cmd);
    return 0;
}

int main()

{



liredictionnaires(compterlignes());

return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

 struct    command
    {
    char    *cmd;
    char    **keyWords;
    };

struct command listecommandesnaturel;



/* This is just a sample code, modify it to meet your need */
int liredictionnaires()
{
    DIR* FD;
    struct dirent* in_file;
    FILE    *entry_file;
    char    cwd[1024];
    char    dossierdictionnaires[50] = "dictionnaires/";
    //char    chaine[100] = "";
    int     count = 0;
    //char    *premiereligne;







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

        char line[256]; /* or other suitable maximum line size */
        while (fgets(line, sizeof (line), entry_file) != NULL) /* read a line */
        {
            if (count == 1)
            {
            //use line or in a function return it
            //in case of a return first close the file with "fclose(file);"

                printf("%s", line);
                count++;
            }
            else
            {
                count++;
            }
        }









        fclose(entry_file);

        strcpy (dossierdictionnaires, "dictionnaires/");
    }

    /* Don't forget to close common file before leaving */

    return 0;
}

int main()

{

liredictionnaires();

return 0;
}

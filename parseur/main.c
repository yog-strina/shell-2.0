#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

/* This is just a sample code, modify it to meet your need */
int liredictionnaires()
{
    DIR* FD;
    struct dirent* in_file;
    FILE    *entry_file;
    char    cwd[1024];


   if (getcwd(cwd, sizeof(cwd)) != NULL)
       fprintf(stdout, "Current working dir: %s\n", cwd);
   else
       perror("getcwd() error");
       return 1;



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
        entry_file = fopen(in_file->d_name, "r");
        if (entry_file == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));

            return 1;
        }





        fclose(entry_file);
    }

    /* Don't forget to close common file before leaving */

    return 0;
}

int main()

{

liredictionnaires();

return 1;
}

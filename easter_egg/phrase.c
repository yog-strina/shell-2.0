#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hanoi.h"

char		**fill_phrase(char **phrase)
{
  int		i;
  size_t	get;
  int		lang;
  FILE		*file;
  char		*line;

  i = 0;
  line = NULL;
  if ((phrase = malloc(sizeof(*phrase) * NB_PHRASE)) == NULL)
    exit(EXIT_FAILURE);
  if ((file = fopen(SETTINGS, "r")) == NULL)
    {
      write(2, BAD_SETTINGS, strlen(BAD_SETTINGS));
      exit(EXIT_FAILURE);
    }
  while (getline(&line, &get, file) != -1 && strstr(line, "langue") == NULL);
  if (strstr(line, "langue") == NULL)
    {
      write(2, BAD_SETTINGS, strlen(BAD_SETTINGS));
      exit(EXIT_FAILURE);
    }
  lang = line[0] - '0';
  fclose(file);
  if ((file = fopen(PHRASE, "r")) == NULL)
    {
      write(2, BAD_PHRASE, strlen(BAD_PHRASE));
      exit(EXIT_FAILURE);
    }
  i = 0;
  line = NULL;
  while (getline(&line, &get, file) != -1 && line[0] - '0' != lang);
  if (line[0] - '0' != lang)
    {
      write(2, BAD_PHRASE, strlen(BAD_PHRASE));
      exit(EXIT_FAILURE);
    }
  i = 0;
  phrase[i] = strdup(line + 1);
  phrase[i][(int)strcspn(phrase[i], "\n")] = '\0';
  get = 0;
  while (++i < NB_PHRASE && getline(&line, &get, file) != -1 && line[0] - '0' == lang)
    {
      phrase[i] = strdup(line + 1);
      phrase[i][(int)strcspn(phrase[i], "\n")] = '\0';
    }
  return (phrase);
}

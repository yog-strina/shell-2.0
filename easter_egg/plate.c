#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hanoi.h"

void    add_plate(Plate **plate, int numPlate, char *namePlate, int colourBg, int colourFg)
{
  Plate *new;
  Plate *tmp;

  tmp = *plate;
  if ((new = malloc(sizeof(*new))) == NULL)
    exit(EXIT_FAILURE);
  new->next = NULL;
  new->prev = NULL;
  new->colourBg = colourBg;
  new->colourFg = colourFg;
  new->namePlate = strdup(namePlate);
  new->numPlate = numPlate;
  if (*plate == NULL)
    *plate = new;
  else
    {
      while (*plate && (*plate)->next)
	*plate = (*plate)->next;
      new->prev = *plate;
      (*plate)->next = new;
      *plate = tmp;
    }
}

char    *get_plate_name(int i)
{
  char  *namePlate;
  char  num[3];
  int   j;
  int   sizePlate;
  char  c;

  bzero(num, 3);
  sprintf(num, "%d", i);
  c = 'a';
  if (i >= 10 && i <= 35)
    {
      c += (i - 10);
      num[0] = c;
      num[1] = 0;
    }
  if (i > 35)
    exit(EXIT_FAILURE);
  sizePlate = sizeof(*namePlate) * (strlen(num) * i * 2 + 1);
  if ((namePlate = malloc(sizePlate)) == NULL)
    exit(EXIT_FAILURE);
  bzero(namePlate, sizePlate);
  j = -1;
  while (++j < i)
    strncat(namePlate, num, strlen(num));
  strncat(namePlate, "|", 1);
  j = -1;
  while (++j < i)
    strncat(namePlate, num, strlen(num));
  return (namePlate);
}

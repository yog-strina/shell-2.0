#include <string.h>
#include "hanoi.h"

int     check_cmd(char buf[2], Tower **tower) /* Fonction qui vérifie la commande de jeu */
{
  int   flag;

  flag = 0;
  while (tower[0]->plate && tower[0]->plate->next && strcmp(tower[0]->plate->namePlate, "|") == 0)
    tower[0]->plate = tower[0]->plate->next;
  while (tower[1]->plate && tower[1]->plate->next && strcmp(tower[1]->plate->namePlate, "|") == 0)
    tower[1]->plate = tower[1]->plate->next;
  while (tower[2]->plate && tower[2]->plate->next && strcmp(tower[2]->plate->namePlate, "|") == 0)
    tower[2]->plate = tower[2]->plate->next;
  if ((buf[0] != '1' && buf[0] != '2' && buf[0] != '3') ||
      (buf[1] != '1' && buf[1] != '2' && buf[1] != '3' && buf[1] != '\n'))
    flag = -1;
  else if (buf[0] == buf[1])
    flag = -1;
  else if (tower[buf[0] - '0' - 1]->nbPlate == 0)
    flag = -1;
  else if (tower[buf[0] - '0' - 1]->plate->numPlate > tower[buf[1] - '0' - 1]->plate->numPlate) /* Vérif\
												   ie que le plateau à déplacer n'est pas plus grand que le plateau sur lequel il doit aller */
    flag = -1;
  while (tower[0]->plate->prev)
    tower[0]->plate = tower[0]->plate->prev;
  while (tower[1]->plate->prev)
    tower[1]->plate = tower[1]->plate->prev;
  while (tower[2]->plate->prev)
    tower[2]->plate = tower[2]->plate->prev;
  return (flag);                /* Retourne flag pour dire comment la commande s'est passée */
}

void    execute_cmd(Tower *tower1, Tower *tower2)
{
  int   numPlate;
  char  *namePlate;
  int   colourFg;
  int   colourBg;

  while (tower1->plate && tower1->plate->next && strcmp(tower1->plate->namePlate, "|") == 0)
    tower1->plate = tower1->plate->next;
  while (tower2->plate && tower2->plate->next && strcmp(tower2->plate->next->namePlate, "|") == 0)
    tower2->plate = tower2->plate->next;
  numPlate = tower2->plate->numPlate;
  colourBg = tower2->plate->colourBg;
  colourFg = tower2->plate->colourFg;
  namePlate = strdup(tower2->plate->namePlate);
  tower2->plate->numPlate = tower1->plate->numPlate;
  tower2->plate->namePlate = strdup(tower1->plate->namePlate);
  tower2->plate->colourFg = tower1->plate->colourFg;
  tower2->plate->colourBg = tower1->plate->colourBg;
  tower1->plate->numPlate = numPlate;
  tower1->plate->namePlate = strdup(namePlate);
  tower1->plate->colourFg = colourFg;
  tower1->plate->colourBg = colourBg;
  tower1->nbPlate--;
  tower2->nbPlate++;
  while (tower1->plate->prev)
    tower1->plate = tower1->plate->prev;
  while (tower2->plate->prev)
    tower2->plate = tower2->plate->prev;
}

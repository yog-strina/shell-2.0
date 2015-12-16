#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "hanoi.h"

void    fill_towers(Tower **tower, int cmplx)
{
  int   i;

  i = -1;
  while (++i < 3)
    if ((tower[i] = malloc(sizeof(**tower))) == NULL)
      exit(EXIT_FAILURE);
  i = 0;
  tower[0]->x = getmaxx(stdscr) / 4;
  tower[0]->y = getmaxy(stdscr) / 2;
  tower[0]->plate = NULL;
  tower[0]->nbPlate = 0;
  while (++i <= cmplx)
    {
      add_plate(&(tower[0]->plate), i, get_plate_name(i), i % 7 + 1, COLOR_BLACK);
      tower[0]->nbPlate++;
    }
  tower[1]->plate = NULL;
  tower[1]->nbPlate = 0;
  tower[1]->x = getmaxx(stdscr) / 2;
  tower[1]->y = getmaxy(stdscr) / 2;
  tower[2]->plate = NULL;
  tower[2]->nbPlate = 0;
  tower[2]->x = getmaxx(stdscr) * 3 / 4;
  tower[2]->y = getmaxy(stdscr) / 2;
  i = 0;
  while (++i <= cmplx)
    {
      add_plate(&(tower[1]->plate), CMPLX_MAX + 1, "|", COLOR_BLACK, COLOR_WHITE);
      add_plate(&(tower[2]->plate), CMPLX_MAX + 1, "|", COLOR_BLACK, COLOR_WHITE);
    }
}

void    disp_towers(Tower **tower, int cmplx)
{
  int   j;
  int   i;
  int   pair;
  Plate *tmp0;
  Plate *tmp1;
  Plate *tmp2;

  tmp0 = tower[0]->plate;
  tmp1 = tower[1]->plate;
  tmp2 = tower[2]->plate;
  i = 0;
  pair = 1;
  while (tower[0]->plate && tower[1]->plate && tower[2]->plate)
    {
      j = -1;
      while (++j < 3)
	{
	  init_pair(pair, tower[j]->plate->colourFg, tower[j]->plate->colourBg);
	  attron(COLOR_PAIR(pair));
	  mvprintw(tower[j]->y - (cmplx - i), tower[j]->x - strlen(tower[j]->plate->namePlate) / 2,
		   "%s", tower[j]->plate->namePlate);
	  attroff(COLOR_PAIR(pair++));
	}
      i++;
      tower[0]->plate = tower[0]->plate->next;
      tower[1]->plate = tower[1]->plate->next;
      tower[2]->plate = tower[2]->plate->next;
    }
  tower[0]->plate = tmp0;
  tower[1]->plate = tmp1;
  tower[2]->plate = tmp2;
  refresh();
}

#include <signal.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include "hanoi.h"

void	my_endwin()
{
  endwin();
}

void	catch_sigint(int sig)	/* Appelée lors de l'interception d'un SIGINT et modifie son action */
{
  (void)sig;
  endwin();			/* Fermeture de la fenêtre de jeu */
  exit(EXIT_SUCCESS);		/* Quitte le programme en précisant que tout a fonctionné */
}

void	add_plate(Plate **plate, int numPlate, char *namePlate, int colourBg, int colourFg)
{
  Plate	*new;
  Plate	*tmp;

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

char	*get_plate_name(int i)
{
  char	*namePlate;
  char	num[3];
  int	j;
  int	sizePlate;
  char	c;

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

void	fill_towers(Tower **tower, int cmplx)
{
  int	i;

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

void	disp_towers(Tower **tower, int cmplx)
{
  int	j;
  int	i;
  int	pair;
  Plate	*tmp0;
  Plate	*tmp1;
  Plate	*tmp2;

  tmp0 = tower[0]->plate;
  tmp1 = tower[1]->plate;
  tmp2 = tower[2]->plate;
  i = 0;
  pair = 0;
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

int	check_cmd(char buf[2], Tower **tower) /* Fonction qui vérifie la commande de jeu */
{
  if ((buf[0] != '1' && buf[0] != '2' && buf[0] != '3') ||
      (buf[1] != '1' && buf[1] != '2' && buf[1] != '3' && buf[1] != '\n'))
    return (-1);	/* Retourne -1 pour dire que la commande est mauvaise */
  if (tower[buf[0] - '0' - 1]->plate->numPlate > tower[buf[1] - '0' - 1]->plate->numPlate) /* Vérifie que le plateau à déplacer n'est pas plus grand que le plateau sur lequel il doit aller */
    return (-1);
  return (0);		/* Retourne 0 pour dire que la commande est bonne */
}

void	execute_cmd(Tower *tower1, Tower *tower2)
{
  int	numPlate;
  char	*namePlate;
  int	colourFg;
  int	colourBg;

  while (tower1->plate && tower1->plate->next && strcmp(tower1->plate->next->namePlate, "|") == 0)
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
  while (tower1->plate->prev)
    tower1->plate = tower1->plate->prev;
  while (tower2->plate->prev)
    tower2->plate = tower2->plate->prev;
}

void		game_loop(int cmplx)	/* Fonction qui fait tourner le jeu en boucle */
{
  Tower		**tower;		/* Tableau de structures qui contient les 3 tours */
  char		cmd[2];
  const int	y = getmaxy(stdscr) / 2 - cmplx * 2;
  const int	x = getmaxx(stdscr) / 4;

  if ((tower = malloc(sizeof(*tower) * 3)) == NULL)
    exit(EXIT_FAILURE);
  fill_towers(tower, cmplx);
  disp_towers(tower, cmplx);
  while (tower[2]->nbPlate != cmplx)
    {
      erase();
      disp_towers(tower, cmplx);
      bzero(cmd, 2);
      mvprintw(y, x, ASK_MOVE);
      mvgetnstr(y + 1, x, cmd, 2);
      if (check_cmd(cmd, tower) == -1)
	mvprintw(y + 2, x, BAD_REQUEST);
      else
	execute_cmd(tower[cmd[0] - '0' - 1], tower[cmd[1] - '0' - 1]);
      disp_towers(tower, cmplx);
    }
}

int	check_cmplxt(char buf[3]) /* Fonction qui vérifie la difficulté */
{
  if ((isdigit(buf[1]) != 0 && buf[2] != '\n') ||	/* Si le dernier char n'est pas un \n */
      atoi(buf) < CMPLX_MIN || atoi(buf) > CMPLX_MAX ||	/* Si la difficulté est inférieur à 3 ou supérieur à 10 */
      isdigit(buf[0]) == 0 ||				/* Si le premier char n'est pas un chiffre */
      (isdigit(buf[1]) == 0 && buf[1] != '\n'))		/* Si le deuxième char n'est pas un chiffre ou un \n */
    return (-1);	/* Retourne -1 pour dire que la difficulté est mauvaise */
  return (0);		/* Retourne 0 pour dire que la difficulté est bonne */
}

void	hanoi_towers()	/* Fonction qui lance la fenêtre de jeu */
{
  char	buf[3];			/* Tableau de char qui va contenir la difficulté */

  atexit(my_endwin);		/* Quand exit() est appelé, la fonction endwin() l'est aussi */
  signal(SIGINT, catch_sigint);	/* Intercepte un SIGINT et modifie son action */
  do
    {
      write(1, ASK_CMPLX, strlen(ASK_CMPLX));	/* Demande le niveau de difficulté */
      printf("(%d-%d)\n", CMPLX_MIN, CMPLX_MAX);
      if (read(1, buf, 3) == -1)		/* Lit le niveau de difficulté et le stock dans buf */
	exit(-1);				/* Quitte en donnant -1 si read() échoue */
    }
  while (check_cmplxt(buf) == -1);		/* Boucle tant que la difficulté n'est pas bonne */
  initscr();		/* Initialise les routines d'ecran et de manipulation */
  start_color();	/* Permet de pouvoir manipuler les couleurs */
  game_loop(atoi(buf));	/* Boucle de jeu */
  endwin();		/* Met fin à la fenêtre */
  exit(EXIT_SUCCESS);	/* Quitte en prévenant que la fonction s'est finie sans problème */
}

int	main()
{
  hanoi_towers();
  return (1);
}

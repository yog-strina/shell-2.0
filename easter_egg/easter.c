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

void	fill_colour(char colour[TAB_COLOUR][COLOUR]) /* Pour remplir le tableau des couleurs */
{
  strcpy(colour[0], ANSI_COLOUR_BLACK_RED);	/* Ces 10 lignes vont servir à copier les chaînes */
  strcpy(colour[1], ANSI_COLOUR_BLACK_GREEN);	/* qui affichent de la couleur dans le tableau */
  strcpy(colour[2], ANSI_COLOUR_BLACK_YELLOW);	/* qui va contenir les couleurs */
  strcpy(colour[3], ANSI_COLOUR_BLACK_BLUE);
  strcpy(colour[4], ANSI_COLOUR_BLACK_PURPLE);
  strcpy(colour[5], ANSI_COLOUR_BLACK_CYAN);
  strcpy(colour[6], ANSI_COLOUR_BLACK_WHITE);
  strcpy(colour[7], ANSI_COLOUR_RED_BLACK);
  strcpy(colour[8], ANSI_COLOUR_CYAN_BLACK);
  strcpy(colour[9], ANSI_COLOUR_YELLOW_BLACK);
}

void	go_to_end(Plate **list)
{
  while ((*list)->next)
    *list = (*list)->next;
}

void	go_to_start(Plate **list)
{
  while ((*list)->prev)
    *list = (*list)->prev;
}

void	add_plate(Plate **plate, int numPlate, char *namePlate)
{
  Plate	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    exit(EXIT_FAILURE);
  new->next = NULL;
  new->prev = NULL;
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
      go_to_start(plate);
    }
}

char	*get_plate_name(int i, char colour[TAB_COLOUR][COLOUR])
{
  char	*namePlate;
  char	num[3];
  int	j;
  int	sizePlate;

  bzero(num, 3);
  sprintf(num, "%d", i + 1);
  sizePlate = sizeof(*namePlate) * (strlen(num) * i * 2 + 1 + COLOUR + COLOUR_RESET);
  if ((namePlate = malloc(sizePlate)) == NULL)
    exit(EXIT_FAILURE);
  bzero(namePlate, sizePlate);
  strncpy(namePlate, colour[i], COLOUR);
  j = -1;
  while (++j < i + 1)
    strncat(namePlate, num, strlen(num));
  strncat(namePlate, "|", 1);
  j = -1;
  while (++j < i + 1)
    strncat(namePlate, num, strlen(num));
  strncat(namePlate, ANSI_COLOUR_RESET, COLOUR_RESET);
  return (namePlate);
}

void	fill_towers(Tower **tower, int cmplx, char colour[TAB_COLOUR][COLOUR])
{
  int	i;

  i = -1;
  while (++i < 3)
    if ((tower[i] = malloc(sizeof(**tower))) == NULL)
      exit(EXIT_FAILURE);
  i = -1;
  tower[0]->x = getmaxx(stdscr) / 4;
  tower[0]->y = getmaxy(stdscr) / 2;
  tower[0]->plate = NULL;
  tower[0]->nbPlate = 0;
  while (++i < cmplx)
    {
      add_plate(&(tower[0]->plate), i, get_plate_name(i, colour));
      tower[0]->nbPlate++;
    }
  tower[1]->plate = NULL;
  tower[1]->nbPlate = 0;
  tower[1]->x = getmaxx(stdscr) / 2;
  tower[1]->y = getmaxy(stdscr) / 2;
  tower[2]->plate = NULL;
  tower[2]->nbPlate = 0;
  tower[2]->x = getmaxx(stdscr) * 0.75;
  tower[2]->y = getmaxy(stdscr) / 2;
  i = -1;
  while (++i < cmplx)
    {
      add_plate(&(tower[1]->plate), 0, "|");
      tower[1]->nbPlate++;
      add_plate(&(tower[2]->plate), 0, "|");
      tower[1]->nbPlate++;
    }
}

void	disp_towers(Tower **tower, int cmplx)
{
  int	i;

  while (tower[0]->plate && tower[1]->plate && tower[2]->plate)
    {
      i = -1;
      while (++i < cmplx - tower[0]->plate->numPlate)
	write(1, " ", 1);
      /* tower[0]->plate->namePlate, tower[1]->plate->namePlate, tower[2]->plate->namePlate */
      tower[0]->plate = tower[0]->plate->next;
      tower[1]->plate = tower[1]->plate->next;
      tower[2]->plate = tower[2]->plate->next;
    }
}

void	game_loop(int cmplx)	/* Fonction boucle qui fait tourner le jeu en boucle */
{
  Tower	**tower;		/* Tableau de structures qui contient les 3 tours */
  char	colour[TAB_COLOUR][COLOUR];		/* Tableau de tableau de char qui contient les couleurs */

  if ((tower = malloc(sizeof(*tower) * 3)) == NULL)
    exit(EXIT_FAILURE);
  tower[4] = NULL;
  fill_colour(colour);		/* Remplit le tableau de couleurs */
  fill_towers(tower, cmplx, colour);
  disp_towers(tower);
  while ("You think this is a motherfucking game ?!");
}

int	check_cmplxt(char buf[3]) /* Fonction qui vérifie la difficulté */
{
  if (atoi(buf) < CMPLX_MIN || atoi(buf) > CMPLX_MAX ||	/* Si la difficulté est inférieur à 3 ou supérieur à 10 */
      isdigit(buf[0]) == 0 ||				/* Si le premier char n'est pas un chiffre */
      (isdigit(buf[1]) == 0 && buf[1] != '\n') ||	/* Si le deuxième char n'est pas un chiffre ou un \n */
      (isdigit(buf[1]) != 0 && buf[2] != '\n'))					/* Si le dernier char n'est pas un \n */
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

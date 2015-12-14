#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <ncurses.h>
#include <unistd.h>
#include "hanoi.h"

void	catch_sigint(int sig)	/* Appelée lors de l'interception d'un SIGINT et modifie son action */
{
  endwin();			/* Fermeture de la fenêtre de jeu */
  exit(EXIT_SUCCESS);		/* Quitte le programme en précisant que tout a fonctionné */
}

void	fill_colour(char colour[10][9]) /* Pour remplir le tableau des couleurs */
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

void	go_to_end(void *list)
{
  while (list->next)
    list = list->next;
}

void	go_to_start(void *list)
{
  while (list->prev)
    list = list->prev;
}

void	add_plate(Plate *plate, int numPlate, char *namePlate)
{
  Plate	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    exit(EXIT_FAILURE);
  new->next = NULL;
  new->prev = NULL;
  new->namePlate = strdup(namePlate);
  new->numPlate = strdup(numPlate);
  if (plate == NULL)
    plate = new;
  else
    {
      while (plate && plate->next)
	plate = plate->next;
      new->prev = plate;
      plate->next = new;
      go_to_start(plate);
    }
}

void	fill_tower(Tower tower[3], int cmplx, char colour[10][9])
{
  tower[0].x = getmaxx(stdscr) / 4;
  tower[0].y = getmaxy(stdscr) / 2
  tower[1].plate = NULL;
  tower[1].nbPlate = 0;
  tower[1].x = getmaxx(stdscr) / 2;
  tower[1].y = getmaxy(stdscr) / 2
  tower[2].plate = NULL;
  tower[2].nbPlate = 0;
  tower[2].x = getmaxx(stdscr) * 0.75;
  tower[2].y = getmaxy(stdscr) / 2
}

void	game_loop(int cmplx)	/* Fonction boucle qui fait tourner le jeu en boucle */
{
  Tower	tower[3];		/* Tableau de structures qui contient les 3 tours */
  char	colour[10][9];		/* Tableau de tableau de char qui contient les couleurs */

  fill_colour(colour);		/* Remplit le tableau de couleurs */
  fill_towers(tower, cmplx);
}

int	check_cmplxt(char buf[3]) /* Fonction qui vérifie la difficulté */
{
  if (atoi(buf) < 3 || atoi(buf) > 10 ||		/* Si la difficulté est inférieur à 3 ou supérieur à 10 */
      isdigit(buf[0]) == 0 ||				/* Si le premier char n'est pas un chiffre */
      (isdigit(buf[1]) == 0 && buf[1] != '\n') ||	/* Si le deuxième char n'est pas un chiffre ou un \n */
      buf[2] != '\n')					/* Si le dernier char n'est pas un \n */
    return (-1);	/* Retourne -1 pour dire que la difficulté est mauvaise */
  return (0);		/* Retourne 0 pour dire que la difficulté est bonne */
}

void	hanoi_towers()	/* Fonction qui lance la fenêtre de jeu */
{
  char	buf[3];			/* Tableau de char qui va contenir la difficulté */

  atexit(endwin);		/* Quand exit() est appelé, la fonction endwin() l'est aussi */
  signal(SIGINT, catch_sigint);	/* Intercepte un SIGINT et modifie son action */
  do
    {
      write(1, ASK_CMPLX, strlen(ASK_CMPLX));	/* Demande le niveau de difficulté */
      if (read(1, buf, 3) == -1)		/* Lit le niveau de difficulté et le stock dans buf */
	exit(-1);				/* Quitte en donnant -1 si read() échoue */
    }
  while (check_cmplxt(buf) == -1)		/* Boucle tant que la difficulté n'est pas bonne */
    initscr();		/* Initialise les routines d'ecran et de manipulation */
  start_color();	/* Permet de pouvoir manipuler les couleurs */
  game_loop(atoi(buf));	/* Boucle de jeu */
  endwin();		/* Met fin à la fenêtre */
  exit(EXIT_SUCCESS);	/* Quitte en prévenant que la fonction s'est finie sans problème */
}

int	main()
{
  hanoi_towers();
}

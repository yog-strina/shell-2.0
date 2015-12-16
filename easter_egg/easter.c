#include <time.h>
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
  exit(EXIT_SUCCESS);		/* Quitte le programme en précisant que tout a fonctionné */
}

void	end_screen(int moves, int t1, int t2)
{
  char	name[6];
  FILE	*score;

  erase();
  mvprintw(getmaxy(stdscr) / 4, getmaxx(stdscr) / 3, "YOU WON!!!");
  mvprintw(getmaxy(stdscr) / 4 + 1, getmaxx(stdscr) / 3,
	   "You made it in %d moves and %d secondes!",
	   moves, t2 - t1);
  refresh();
  mvprintw(getmaxy(stdscr) / 4 + 2, getmaxx(stdscr) / 3, "Enter your name: ");
  mvgetnstr(getmaxy(stdscr) / 4 + 2, getmaxx(stdscr) / 3 + 17, name, 6);
  if ((score = fopen("score.txt", "a")) == NULL)
    exit(EXIT_FAILURE);
  fprintf(score, "PLAYER: \"%s\"\tTIME: %ds\tMOVES:%d\n",
	  name, t2 - t1, moves);
  exit(EXIT_SUCCESS);
}

void		game_loop(int cmplx)	/* Fonction qui fait tourner le jeu en boucle */
{
  Tower		**tower;		/* Tableau de structures qui contient les 3 tours */
  char		cmd[2];
  const int	y = getmaxy(stdscr) / 2 - cmplx * 2;
  const int	x = getmaxx(stdscr) / 4;
  int		moves;
  time_t	t1;
  time_t	t2;

  moves = 0;
  if ((tower = malloc(sizeof(*tower) * 3)) == NULL)
    exit(EXIT_FAILURE);
  fill_towers(tower, cmplx);
  disp_towers(tower, cmplx);
  t1 = time(NULL);
  while (tower[2]->nbPlate != cmplx)
    {
      erase();
      disp_towers(tower, cmplx);
      bzero(cmd, 2);
      mvprintw(y, x, ASK_MOVE);
      mvgetnstr(y + 1, x, cmd, 2);
      while (check_cmd(cmd, tower) == -1)
	{
	  mvprintw(y + 2, x, BAD_REQUEST);
	  mvgetnstr(y + 1, x, cmd, 2);
	}
      execute_cmd(tower[cmd[0] - '0' - 1], tower[cmd[1] - '0' - 1]);
      moves++;
      disp_towers(tower, cmplx);
    }
  t2 = time(NULL);
  end_screen(moves, (int)t1, (int)t2);
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

  atexit(my_endwin);		/* Quand exit() est appelé, la fonction my_endwin() l'est aussi */
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

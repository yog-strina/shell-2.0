/* Inclusion de tous les fichiers headers contenant les fonctions cruciales au programme */
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
#include "hanoi.h"		/* Header contenant les fonctions créées pour ce programme */
/*********************************************************************************/
void	my_endwin()		/* Fonction comme endwin() mais qui ne prend rien et ne renvoie rien */
{
  endwin();			/* Ferme la fenêtre */
}

void	catch_sigint(int sig)	/* Appelée lors de l'interception d'un SIGINT et modifie son action */
{
  (void)sig;			/* Effectue une opération sur sig afin d'éviter un warning de non-utilisation */
  exit(EXIT_SUCCESS);		/* Quitte le programme en précisant que tout a fonctionné */
}

void	end_screen(int moves, int t1, int t2, char **phrase) /* Ecran de fin et ecriture du score */
{
  char	key[1];			/* Utilisée pour récupérer un appuie sur la touche entrée */
  char	*name;			/* Contient le nom de l'utilisateur */
  FILE	*score;			/* Contient le fichier de score */

  erase();			/* Efface l'ecran */
  mvprintw(getmaxy(stdscr) / 4, getmaxx(stdscr) / 3, phrase[VICTORY]); /* Affiche la phrase de victoire */
  mvprintw(getmaxy(stdscr) / 4 + 1, getmaxx(stdscr) / 3,
	   "%s%d%s%d%s",
	   phrase[U_MADE_IT], moves, phrase[MOVES_AND], t2 - t1, phrase[SECONDES]); /* Affiche le temps et le nombre de mouvements */
  refresh();			/* Actualise l'ecran */
  mvprintw(getmaxy(stdscr) / 4 + 2, getmaxx(stdscr) / 3, phrase[PRESS_ENTER]); /* Demande d'appuyer sur entrée */
  noecho();			/* N'affiche pas à l'ecran ce qui est tapé au clavier */
  mvgetnstr(getmaxy(stdscr) / 4 + strlen(phrase[PRESS_ENTER]) + 1, getmaxx(stdscr) / 3, key, 0); /* Récupére l'entrée de l'utilisateur */
  echo();			/* Réaffiche ce qui est tapé au clavier */
  if ((score = fopen("score.txt", "a")) == NULL) /* Ouvre score.txt ou le crée si il n'existe pas et vérifie que la fonction s'est bien déroulée */
    exit(EXIT_FAILURE);				 /* Quitte en précisant qu'il y a eu un problème */
  name = strdup(getenv("USER"));		 /* Récupère le nom de l'utilisateur */
  fprintf(score, "PLAYER: %s\tTIME: %ds\tMOVES:%d\n", /* Écrit le nom du joueur, le temps et les mouvements dans le fichier score */
	  name, t2 - t1, moves);
  exit(EXIT_SUCCESS);		/* Quitte en précisant que tout s'est bien passé */
}

void		game_loop(int cmplx, char **phrase)	/* Fonction qui fait tourner le jeu en boucle */
{
  Tower		**tower;		/* Tableau de pointeurs sur structures qui contient les 3 tours */
  char		cmd[2];			/* Va contenir la commande rentrée par l'utilisateur */
  const int	y = getmaxy(stdscr) / 2 - cmplx * 2; /* Constantes contenant les coordonnées où afficher les éléments du jeu */
  const int	x = getmaxx(stdscr) / 4;
  int		moves;		/* Contient le nombre de mouvements effectués */
  time_t	t1;		/* Contient le temps de début */
  time_t	t2;		/* Contient le temps de fin */

  moves = 0;
  if ((tower = malloc(sizeof(*tower) * 3)) == NULL)
    exit(EXIT_FAILURE);
  fill_towers(tower, cmplx);	/* Rempli les tours */
  disp_towers(tower, cmplx);	/* Affiche les tours */
  t1 = time(NULL);		/* Met le temps du début du jeu dans t1 */
  while (tower[2]->nbPlate != cmplx) /* Boucle tant que la dernière tour n'est pas rempli */
    {
      erase();			/* Efface l'ecran */
      disp_towers(tower, cmplx); /* Affiche les tours */
      bzero(cmd, 2);		 /* Rempli cmd avec des '\0' */
      mvprintw(0, 0, "%d", moves); /* Affiche le nombre de mouvements effectués aux coordonnées 0,0 */
      mvprintw(y, x, phrase[ASK_MOVE]); /* Demande de rentrer un mouvement en x,y */
      mvgetnstr(y, x + strlen(phrase[ASK_MOVE]) + 1, cmd, 2); /* Stocke l'entrée dans cmd */
      while (check_cmd(cmd, tower) == -1)		      /* Boucle qui vérifie la commande */
	{
	  mvprintw(y + 2, x, phrase[BAD_MOVE]); /* Dit que la commande est mauvaise */
	  mvgetnstr(y + 1, x, cmd, 2);		/* Stocke la commande */
	}
      execute_cmd(tower[cmd[0] - '0' - 1], tower[cmd[1] - '0' - 1]); /* Exécute la commande */
      moves++;			/* Augmente le nombre de mouvements effectué de 1 */
      disp_towers(tower, cmplx); /* Affiche les tours */
    }
  t2 = time(NULL);		/* Met le temps de fin du jeu dans t2 */
  end_screen(moves, (int)t1, (int)t2, phrase); /* Affiche l'ecran de fin */
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
  char	**phrase;		/* Tableau de tableau qui va contenir les phrases à afficher en fonction du langage */

  phrase = NULL;		/* Initialisation du char **phrase */
  phrase = fill_phrase(phrase);	/* Remplissage des phrases */
  atexit(my_endwin);		/* Quand exit() est appelé, la fonction my_endwin() l'est aussi */
  signal(SIGINT, catch_sigint);	/* Intercepte un SIGINT et modifie son action */
  do
    {
      write(1, phrase[ASK_CMPLX], strlen(phrase[ASK_CMPLX]));	/* Demande le niveau de difficulté */
      printf(" (%d-%d)\n", CMPLX_MIN, CMPLX_MAX);
      if (read(1, buf, 3) == -1)		/* Lit le niveau de difficulté et le stock dans buf */
	exit(-1);				/* Quitte en donnant -1 si read() échoue */
    }
  while (check_cmplxt(buf) == -1);		/* Boucle tant que la difficulté n'est pas bonne */
  initscr();		/* Initialise les routines d'ecran et de manipulation */
  start_color();	/* Permet de pouvoir manipuler les couleurs */
  game_loop(atoi(buf), phrase);	/* Boucle de jeu */
  endwin();		/* Met fin à la fenêtre */
  exit(EXIT_SUCCESS);	/* Quitte en prévenant que la fonction s'est finie sans problème */
}

int	main()
{
  hanoi_towers();
  return (1);
}

#ifndef	_HANOI_H_
# define _HANOI_H_

# define ASK_CMPLX	0
# define ASK_MOVE	1
# define BAD_MOVE	2
# define VICTORY	3
# define U_MADE_IT	4
# define MOVES_AND	5
# define SECONDES	6
# define ENTER_NAME	7
# define BAD_PHRASE	"Phrases file is badly formated\n"
# define BAD_SETTINGS	"Settings is badly formated\n"
# define SETTINGS	"settings.config"
# define PHRASE		".phrase.txt"
# define NB_PHRASE	8
# define CMPLX_MIN	3
# define CMPLX_MAX	10

typedef struct	Plate
{
  int		numPlate;
  int		colourBg;
  int		colourFg;
  char		*namePlate;
  struct Plate	*next;
  struct Plate	*prev;
}		Plate;

typedef struct	Tower
{
  int		x;
  int		y;
  int		nbPlate;
  Plate		*plate;
}		Tower;

void	add_plate(Plate **plate, int numPlate, char *namePlate, int colourBg, int colourFg);
void	catch_sigint(int sig);
int	check_cmd(char buf[2], Tower **tower);
int	check_cmplxt(char buf[3]);
void	disp_towers(Tower **tower, int cmplx);
void	end_screen(int moves, int t1, int t2, char **phrase);
void	execute_cmd(Tower *tower1, Tower *tower2);
void	fill_towers(Tower **tower, int cmplx);
char	**fill_phrase(char **phrase);
void	game_loop(int cmplx, char **phrase);
char	*get_plate_name(int i);
void	hanoi_towers();
void	my_endwin();

#endif /* !_HANOI_H_ */

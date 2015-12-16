#ifndef	_HANOI_H_
# define _HANOI_H_

# define ASK_CMPLX			"Choose a complexity level "
# define ASK_MOVE			"Choose a move:"
# define BAD_REQUEST			"Bad move"
# define CMPLX_MIN			3
# define CMPLX_MAX			10

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
void	end_screen(int moves, int t1, int t2);
void	execute_cmd(Tower *tower1, Tower *tower2);
void	fill_towers(Tower **tower, int cmplx);
void	game_loop(int cmplx);
char	*get_plate_name(int i);
void	hanoi_towers();
void	my_endwin();

#endif /* !_HANOI_H_ */

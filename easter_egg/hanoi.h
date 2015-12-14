#ifndef	_HANOI_H_
# define _HANOI_H_

# define ASK_CMPLX			"Choisissez un niveau de difficulté (3-10)\n"
# define ANSI_COLOUR_RESET		"\x1b[0m"
# define ANSI_COLOUR_BLACK_RED		"\033[30;41m"
# define ANSI_COLOUR_BLACK_GREEN	"\033[30;42m"
# define ANSI_COLOUR_BLACK_YELLOW	"\033[30;43m"
# define ANSI_COLOUR_BLACK_BLUE		"\033[30;44m"
# define ANSI_COLOUR_BLACK_PURPLE	"\033[30;45m"
# define ANSI_COLOUR_BLACK_CYAN		"\033[30;46m"
# define ANSI_COLOUR_BLACK_WHITE	"\033[30;47m"
# define ANSI_COLOUR_RED_BLACK		"\033[31;40m"
# define ANSI_COLOUR_CYAN_BLACK		"\033[36;40m"
# define ANSI_COLOUR_YELLOW_BLACK	"\033[33;40m"
# define COLOUR				9
# define COLOUR_RESET			5
# define TAB_COLOUR			10
# define CMPLX_MIN			3
# define CMPLX_MAX			10

typedef struct	Plate
{
  int		numPlate;
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

#endif /* !_HANOI_H_ */

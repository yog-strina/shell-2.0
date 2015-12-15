#ifndef	_HANOI_H_
# define _HANOI_H_

# define ASK_CMPLX			"Choisissez un niveau de difficulté "
# define ASK_MOVE			"Choisissez un mouvement:"
# define BAD_REQUEST			"Mauvais mouvement, rtfm"
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

#endif /* !_HANOI_H_ */

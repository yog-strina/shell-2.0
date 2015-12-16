NAME	=	hanoi

SRCS	= 	easter.c \
	  	game_cmd.c \
		plate.c \
		tower.c

CFLAGS	+=	-W -Wall -Wextra -ansi -pedantic -D_GNU_SOURCE -g

LDFLAGS	+=	-lncurses

OBJS	= 	$(SRCS:.c=.o)

CC	= 	gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJS)
	rm -f *~

fclean: clean
	rm -f $(NAME)

re: fclean all

full: re
	make clean

NAME	=	shell2.0

SRCS	= 	easter.c

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

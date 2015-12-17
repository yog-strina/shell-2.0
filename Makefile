NAME	=	shell2.0

SRCS	=	expert_shell.c \
		parser.c \
		assist_en.c \
		menu1_en.c \
		menu2_en.c \
		menu3_en.c \
		menu4_en.c \
		menu5_en.c \
		assist_fr.c \
		menu1_fr.c \
		menu2_fr.c \
		menu3_fr.c \
		menu4_fr.c \
		menu5_fr.c \
		main.c \
		easter.c \
	  	game_cmd.c \
		plate.c \
		tower.c \
	  	phrase.c

LDFLAGS	+=	-lncurses

OBJS	= 	$(SRCS:.c=.o)

CC	= 	gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS)
	rm -f *~

fclean: clean
	rm -f $(NAME)

re: fclean all

full: re
	make clean

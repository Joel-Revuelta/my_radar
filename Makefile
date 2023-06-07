##
## EPITECH PROJECT, 2022
## CPool_10
## File description:
## Makefile
##

T_SRC	= 	main.c				\
			my_radar.c			\
			csfml_objects.c		\
			init_radar.c		\
			events.c			\
			display.c			\
			create_window.c		\
			collisions.c		\
			planes.c			\
			in_tower.c			\
			get_things.c

PREFIX = src/

SRC = $(addprefix $(PREFIX), $(T_SRC))

NAME = my_radar

CC = gcc

CFLAGS = -g3 -W -Wall -Wextra -Werror -I include/ -L lib/ -lmy
CSFML =  -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

OBJ	=	$(SRC:.c=.o)

all: 	$(NAME)

$(NAME): dolib $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(CSFML)

dolib:
	cd lib; make

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f *.gcda
	rm -f *.gcno
	cd lib; make clean

fclean:	clean
	rm -f $(NAME)
	rm -f $(T_NAME)
	cd lib; make fclean

re:	fclean all
	make clean

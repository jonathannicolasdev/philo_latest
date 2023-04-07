PROG	= philo

SRCS 	= srcs/main.c srcs/utils.c srcs/init.c srcs/dinner.c srcs/state_observer.c srcs/start.c \
			srcs/dinner_utils.c srcs/init_utils.c srcs/utils_utils.c srcs/utils_utils_utils.c

OBJS 	= ${SRCS:.c=.o}

HEADER	= -Iinclude

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g
SANIT   = #-fsanitize=thread

.c.o:		
					@$(CC) ${CFLAGS} ${SANIT} ${HEADER} -c $< -o $(<:.c=.o)

all:	${PROG}

${PROG}:	${OBJS}
					@$(CC) ${SANIT} ${OBJS} -o ${PROG} -lpthread
					@echo "\n\033[32m\033[1m  Philosophers Compiled\n\033[0m"

clean:
					@rm -f ${OBJS}

fclean: 	clean
					@rm -f ${PROG}

re:			fclean all

.PHONY: all clean fclean re
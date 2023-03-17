PROG	= philo

SRCS 	= srcs/main.c srcs/utils.c srcs/init.c srcs/dinner.c srcs/start.c srcs/time.c

OBJS 	= ${SRCS:.c=.o}

HEADER	= -Iinclude

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g

.c.o:		
					@$(CC) ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all:	${PROG}

${PROG}:	${OBJS}
					@$(CC) ${OBJS} -o ${PROG} -lpthread
					@echo "\n\033[32m\033[1m  Philosophers Compiled\n\033[0m"

clean:
					@rm -f ${OBJS}

fclean: 	clean
					@rm -f ${PROG}

re:			fclean all

emote:	
					@echo "▒▒▒▒▒▒▒▒▄▄▄▄▄▄▄▄▄▄▒▒▒▒▒▒▒▒"
					@echo "▒▒▒▒▒▄█▀▀░░░░░░░░▀▀█▄▒▒▒▒▒"
					@echo "▒▒▒▄█▀▄██▄░░░░░░░░░░▀█▄▒▒▒"
					@echo "▒▒█▀░▀░░▄▀░░░░░░▄▀▀▀▀░▀█▒▒"
					@echo "▒█▀░░░░███░░░░░░▄█▄░░░░▀█▒"
					@echo "▒█░░░░░░▀░░░░░░░▀█▀░░░░░█▒"
					@echo "▒█░░░░░░░░░░░░░░░░░░░░░░█▒"
					@echo "▒█░░██▄░░▀▀▀▀▄▄░░░░░░░░░█▒"
					@echo "▒▀█░█░█░░░▄▄▄▄▄░░░░░░░░█▀▒"
					@echo "▒▒▀█▀░▀▀▀▀░▄▄▄▀░░░░░░▄█▀▒▒"
					@echo "▒▒▒█░░░░░░▀█░░░░░░░▄█▀▒▒▒▒"
					@echo "▒▒▒█▄░░░░░▀█▄▄▄▄▄█▀▀▒▒▒▒▒▒"
					@echo "▒▒▒▒▀▀▀▀▀▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n"

.PHONY: all clean fclean re
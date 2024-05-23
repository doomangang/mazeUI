NAME    = mazeUI
SRCS    = ./source/*.c
OBJS    = ${SRCS:.c=.o}

HEADER  = ./header/*.h

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f

# Define build types
DEBUG_CFLAGS = -g
RELEASE_CFLAGS = -O2

all: ${NAME}

debug: CFLAGS += ${DEBUG_CFLAGS}
debug: clean ${NAME}

release: CFLAGS += ${RELEASE_CFLAGS}
release: clean ${NAME}

%.o: %.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} out.txt

re: fclean all

.PHONY : all clean fclean re debug release

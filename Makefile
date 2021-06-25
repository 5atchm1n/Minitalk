SNAME = server
CNAME = client

INC = minitalk.h

SRC_C = mn_client.c \
		mn_utils.c

SRC_S = mn_server.c \
		mn_utils.c

OBJSDIR = objs

CC = clang

CFLAGS = -Wall -Werror -Wextra -g
MEM = -fsanitize=address
CFLAGS += -MMD -MP

OBJ_C = $(addprefix ${OBJDIR}/,${SRC_C:.c=.o})
OBJ_S = $(addprefix ${OBJDIR}/,${SRC_S:.c=.o})

DEP = ${OBJS:.o=.d}

all : ${SNAME} ${CNAME}

${SNAME}: ${OBJ_S}
	${CC} ${CFLAGS} -I./inc -c $< -o $@

${CNAME}: ${OBJ_C}
	${CC} ${CFLAGS} -I./inc -c $< -o $@

${OBJDIR}/%.o:src/%.c
	${CC} ${CFLAGS} -I./inc -c $< -o $@

re: fclean all

clean:
	@echo  "Cleaning objects\c"
	@rm -rf ${OBJDIR}
	@echo "\033[32m\t[OK]\033[0m"

fclean: clean
	@echo  "Removing minitalk\c"
	@rm -rf ${SNAME} ${CNAME}
	@echo "\033[32m\t\t[OK]\033[0m"

.PHONY : all clean re fclean

-include ${DEP}

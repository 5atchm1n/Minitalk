SNAME = server
CNAME = client

SHELL = bash

INC = minitalk.h

SRC_C = mn_client.c

SRC_S = mn_server.c

LIBFT = inc/libft/libft.a

OBJDIR = objs
SRCDIR = src

CC = clang

CFLAGS = -Wall -Werror -Wextra -g
MEM = -fsanitize=address
CFLAGS += -MMD -MP

OS = $(shell uname -s)

ifeq (OS, Linux)
	CFLAGS += -DOS
endif

OBJ_C = $(addprefix ${OBJDIR}/,${SRC_C:.c=.o})
OBJ_S = $(addprefix ${OBJDIR}/,${SRC_S:.c=.o})

DEP = ${OBJS:.o=.d}

all : ${SNAME} ${CNAME}

$(SNAME) : ${LIBFT} ${OBJ_S}
	${CC} ${CFLAGS} ${MEM} ${OBJ_S} ${LIBFT} -o $@

$(CNAME): ${LIBFT} ${OBJ_C}
	${CC} ${CFLAGS} ${MEM} ${OBJ_C} ${LIBFT} -o $@

$(LIBFT):
	@make -s -C inc/libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -I./inc -c $< -o $@

re: fclean all

clean:
	@echo -ne "Cleaning objects"
	@rm -rf ${OBJDIR}
	@echo -e "\033[32m\t\t[OK]\033[0m"
	@make clean -s -C inc/libft

fclean: clean
	@echo -ne  "Removing minitalk"
	@rm -rf ${SNAME} ${CNAME}
	@echo -e "\033[32m\t\t[OK]\033[0m"
	@make fclean -s -C inc/libft

.PHONY : all clean re fclean

-include ${DEP}

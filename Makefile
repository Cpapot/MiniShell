#				______ _ _
#				|  ____(_) |
#				| |__   _| | ___  ___
#				|  __| | | |/ _ \/ __|
#				| |    | | |  __/\__ \.
#				|_|    |_|_|\___||___/

HEADERS 	=	minishell.h error.h exec.h

SRCS		=	minishell.c minishell_utils.c \
				parsing.c parsing_utils.c shell_split.c \
				split_pipe.c history.c signals.c \
				swap_env.c quote.c check_error.c \
				TEST.c bi_echo.c bi_utils.c bi_env.c \
				bi_pwd.c bi_export.c execution.c bi_cd.c \
				bi_exit.c exit_status.c error.c

LIBFTSRC	=	libftprintf.a libft.a printffd.a

#					Directories

HEADERSDIR	=	./inc/

SRCSDIR		=	./srcs/

LIBFTDIR	=	./libft/

OBJSDIR		=	./.objs/

#					Full Path

HEAD		=	$(addprefix $(HEADERSDIR),$(HEADERS))

SRCSPATH	=	$(addprefix $(SRCSDIR),$(SRCS))

LIBFT		=	$(addprefix $(LIBFTDIR),$(LIBFTSRC))

OBJS	=	$(SRCSPATH:$(SRCSDIR)%.c=$(OBJSDIR)%.o)

#		 __      __        _       _     _
#		 \ \    / /       (_)     | |   | |
#		  \ \  / /_ _ _ __ _  __ _| |__ | | ___  ___
#		   \ \/ / _` | '__| |/ _` | '_ \| |/ _ \/ __|
#		    \  / (_| | |  | | (_| | |_) | |  __/\__ \.
#		     \/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/

RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
DEFAULT		=	\033[0m
SUPPR		=	\r\033[2K

NAME		=	minishell

AR			=	ar rc

CFLAGS		=	-Wall -Wextra -Werror -lreadline5 -g3

CC			=	cc

RM			=	rm -rf

MKDIR		=	mkdir -p

#				  _____       _
#				 |  __ \     | |
#				 | |__) |   _| | ___  ___
#				 |  _  / | | | |/ _ \/ __|
#				 | | \ \ |_| | |  __/\__ \.
#				 |_|  \_\__,_|_|\___||___/

all : PRINTMINISHELL ${NAME}

${NAME}: $(OBJS)
	@${MAKE} --no-print-directory lib
	@${CC} ${OBJS} ${LIBFT} -o ${NAME} -lreadline
	@echo -n "${SUPPR}	${GREEN}${NAME} : 🆗${DEFAULT}\n\n"


$(OBJSDIR)%.o: ${SRCSDIR}%.c ${HEAD}
	@$(eval PRINTMINISHELL = @:)
	@$(MKDIR) .objs
	@echo -n "${YELLOW}${SUPPR}	⌛ Creating minishell objects : $@"
	@$(CC) ${CFLAGS} -c $< -o $@ -I$(HEADERSDIR)

clean:
	@${MAKE} clean -C ${LIBFTDIR}
	@${RM} ${OBJS}

fclean:
	@echo "${RED}🗑  ${NAME} cleanded"
	@echo "${RED}🗑  .log cleanded"
	@${RM} .log
	@${RM} ${OBJS}
	@${RM} ${OBJSDIR}
	@${RM} ${NAME}
	@${MAKE} fclean --no-print-directory -C ${LIBFTDIR}

re:
	@${MAKE} --no-print-directory fclean
	@${MAKE} --no-print-directory all

lib:
	@echo -n "${YELLOW}${SUPPR}	⌛ Compiling libft & printf"
	@${MAKE}	-C ${LIBFTDIR}

PRINTMINISHELL	:
	@echo "\033[1;34m\033[5G=========================================================="
	@echo "\033[1;31m███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      "
	@echo "████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██"
	@echo "██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██"
	@echo "██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██"
	@echo "██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████"
	@echo "\033[1;34m\033[5G==========================================================\n"

.PHONY : re all clean fclean printf lib

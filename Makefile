#				______ _ _
#				|  ____(_) |
#				| |__   _| | ___  ___
#				|  __| | | |/ _ \/ __|
#				| |    | | |  __/\__ \.
#				|_|    |_|_|\___||___/

HEADERS 	=	minishell.h error.h

SRCS		=	minishell.c minishell_utils.c \
				parsing.c parsing_utils.c shell_split.c \
				split_pipe.c history.c signals.c \
				swap_env.c quote.c check_error.c \
				TEST.c bi_echo.c bi_utils.c bi_env.c \
				bi_pwd.c bi_export.c bi_cd.c bi_exit.c \
				exit_status.c error.c bi_unset.c prompt.c \
				execution.c exec_utils.c exec_invoke.c \
				exec_pid.c exec_redir.c fd_utils.c \
				parsing_redir.c


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

CFLAGS		=	-Wall -Wextra -Werror -g3

CC			=	cc

RM			=	rm -rf

MKDIR		=	mkdir -p

#				  _____       _
#				 |  __ \     | |
#				 | |__) |   _| | ___  ___
#				 |  _  / | | | |/ _ \/ __|
#				 | | \ \ |_| | |  __/\__ \.
#				 |_|  \_\__,_|_|\___||___/

all : PRINTMINISHELL lib ${NAME}

${NAME}: $(OBJS) $(LIBFT)
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
	@echo "${RED}🗑  valgrind.txt cleanded"
	@${RM} .log
	@${RM} valgrind.txt
	@${RM} ${OBJS}
	@${RM} ${OBJSDIR}
	@${RM} ${NAME}
	@${MAKE} fclean --no-print-directory -C ${LIBFTDIR}

re:
	@${MAKE} --no-print-directory fclean
	@${MAKE} --no-print-directory all

lib:
	@${MAKE} --no-print-directory -C ${LIBFTDIR}

leaks:	all
		@${RM} valgrind.txt
		echo "{" > valgrind_ignore_leaks.txt
		echo "leak readline" >> valgrind_ignore_leaks.txt
		echo "	Memcheck:Leak" >> valgrind_ignore_leaks.txt
		echo "	..." >> valgrind_ignore_leaks.txt
		echo "	fun:readline" >> valgrind_ignore_leaks.txt
		echo "}" >> valgrind_ignore_leaks.txt
		echo "{" >> valgrind_ignore_leaks.txt
		echo "	leak add_history" >> valgrind_ignore_leaks.txt
		echo "	Memcheck:Leak" >> valgrind_ignore_leaks.txt
		echo "	..." >> valgrind_ignore_leaks.txt
		echo "	fun:add_history" >> valgrind_ignore_leaks.txt
		echo "}" >> valgrind_ignore_leaks.txt
		valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full \
			--show-leak-kinds=all --track-fds=yes \
			--show-mismatched-frees=yes --read-var-info=yes \
			 --log-file=valgrind.txt -s --trace-children=yes ./${NAME}

PRINTMINISHELL	:
	@echo "\033[1;34m\033[5G=========================================================="
	@echo "\033[1;31m███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      "
	@echo "████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██"
	@echo "██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██"
	@echo "██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██"
	@echo "██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████"
	@echo "\033[1;34m\033[5G==========================================================\n"

.PHONY : re all clean fclean printf lib

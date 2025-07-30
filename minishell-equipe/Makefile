BOLD            = "\033[1m"
RESET           = "\033[0m"
GREEN           = "\033[0;32m"
CYAN            = "\033[0;36m"
LIGHT_RED       = "\033[91m"
LIGHT_GREEN     = "\033[92m"
LIGHT_CYAN      = "\033[96m"
BROWN           = "\033[38;5;94m"

NEON_GREEN      = "\033[38;5;46m"
ELECTRIC_BLUE   = "\033[38;5;51m"
HOT_PINK        = "\033[38;5;198m"
BLOOD_RED       = "\033[38;5;196m"
SUNBURST_YELLOW = "\033[38;5;226m"
DEEP_ORANGE     = "\033[38;5;208m"
PURPLE_RAVE     = "\033[38;5;129m"
CYAN_SHOCK      = "\033[38;5;51m"

NAME	= minishell
CC		= cc 
CFLAGS	= -Wall -Werror -Wextra -g3

INCS	= minishell.h

SRCS 	=  exec/execution.c\
		    exec/child_process_exec.c\
			exec/expansion.c\
			exec/path_cmd.c\
			exec/pipes.c\
			exec/builtin/cd.c\
			exec/builtin/echo.c\
			exec/builtin/env.c\
			exec/builtin/exit.c\
			exec/builtin/export.c\
			exec/builtin/pwd.c\
			exec/builtin/unset.c\
			exec/here_doc.c \
			exec/expand_heredoc.c\
			pars/list_creation.c\
			pars/parsing_functions.c\
			pars/args_cmds.c\
			pars/dollar_hanling_functions.c\
			pars/get_return_code.c\
			pars/redirection_in.c\
			pars/redirection_out.c\
			pars/tokenisation.c\
			pars/print_command_error.c\
			pars/chained_list_env_variables.c\
			pars/parse_error.c\
			utils/path_cmd_utils.c\
			utils/builtin_utils2.c\
			utils/free_memory.c\
			utils/return_code.c\
			utils/ft_itoa.c\
			utils/minishell_utils.c\
			utils/minishell_utils2.c\
			utils/minishell_utils3.c\
			utils/utils_heredoc.c\
			utils/utils_heredoc2.c\
			utils/utils_execution.c\
			utils/redirection_checker.c\
			utils/syntax_error_token.c\
			utils/builtin_utils.c\
			utils/lists_initialisation.c\
			utils/gc.c\
			main.c\
			signals.c


OBJS = ${SRCS:.c=.o}

all: ${NAME}

%.o: %.c 
	@$(CC) $(CFLAGS) -I. -c $< -o $@

${NAME}: ${OBJS} ${INCS}

	@echo $(LIGHT_GREEN) "Compilation..."$(BOLD)
	@${CC} ${CFLAGS} ${OBJS} -lreadline  -lhistory -o  ${NAME}
	@echo $(LIGHT_GREEN)"Compilation réussie ✔"$(RESET)

clean:
	@rm -f ${OBJS}
	@echo $(BROWN)clean reussi

fclean: clean
	@rm -f ${NAME}
	@echo $(BROWN)fclean reussi

child: all
	valgrind --suppressions=minishell.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell

nochild: all
	valgrind --suppressions=minishell.supp --leak-check=full --show-leak-kinds=all --trace-children=no --track-fds=yes ./minishell

re: fclean all

.PHONY : re fclean clean all
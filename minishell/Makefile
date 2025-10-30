# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/14 21:59:24 by jubaldo           #+#    #+#              #
#    Updated: 2024/02/04 15:46:29 by jubaldo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCS		=	srcs/builtins/cd.c 						\
				srcs/builtins/echo.c					\
				srcs/builtins/env.c						\
				srcs/builtins/exit.c					\
				srcs/builtins/export.c					\
				srcs/builtins/pwd.c						\
				srcs/builtins/unset.c					\
				srcs/env/env_var_remove.c				\
				srcs/env/get_env_var.c					\
				srcs/env/is_valid_var_name.c			\
				srcs/env/set_env_var.c					\
				srcs/exec/exec_builtin_empty.c			\
				srcs/exec/exec_builtins.c				\
				srcs/exec/exec_child.c					\
				srcs/exec/execute_local.c				\
				srcs/exec/execute_path.c				\
				srcs/exec/execute.c						\
				srcs/init/init_cmd.c					\
				srcs/init/init_commands.c				\
				srcs/init/init_data.c					\
				srcs/init/init_parentheses.c			\
				srcs/init/init_pipes.c					\
				srcs/init/init_redirections.c			\
				srcs/lexer/add_token.c					\
				srcs/lexer/lexer_errors.c				\
				srcs/lexer/lexer_operator.c				\
				srcs/lexer/lexer_parentheses.c			\
				srcs/lexer/lexer_redirection.c			\
				srcs/lexer/tokenize_input.c				\
				srcs/main/main.c						\
				srcs/main/minishell.c					\
				srcs/parser/add_arg_to_cmd.c			\
				srcs/parser/add_parsed_token.c			\
				srcs/parser/parse_dollar_sign.c			\
				srcs/parser/parse_env_exp.c				\
				srcs/parser/parse_export.c				\
				srcs/parser/parse_full_redirections.c	\
				srcs/parser/parse_path.c				\
				srcs/parser/parse_redirections.c		\
				srcs/parser/parse_rm_redirections.c		\
				srcs/parser/parse_split.c				\
				srcs/parser/parse_whitespace.c			\
				srcs/parser/parser.c					\
				srcs/pipes/check_pipes.c				\
				srcs/pipes/close_pipes.c				\
				srcs/pipes/create_pipes.c				\
				srcs/redirection/handle_redirect.c		\
				srcs/redirection/heredoc.c				\
				srcs/redirection/input.c				\
				srcs/redirection/output.c				\
				srcs/redirection/redirect_io.c			\
				srcs/signals/signal_handler.c			\
				srcs/utils/check_args.c					\
				srcs/utils/check_operator.c				\
				srcs/utils/clean.c						\
				srcs/utils/clean2.c 					\
				srcs/utils/error_msg.c					\
				srcs/utils/exit_minishell.c				\
				srcs/utils/get_path.c					\
				srcs/utils/get_prompt.c					\
				srcs/utils/input_handler.c				\
				srcs/utils/is_trucnuche.c				\
				srcs/libft/ft_atol.c					\
				srcs/libft/ft_calloc.c					\
				srcs/libft/ft_isalnum.c					\
				srcs/libft/ft_isalpha.c					\
				srcs/libft/ft_isdigit.c					\
				srcs/libft/ft_itoa.c					\
				srcs/libft/ft_memset.c					\
				srcs/libft/ft_memcpy.c					\
				srcs/libft/ft_putchar.c					\
				srcs/libft/ft_putendl_fd.c				\
				srcs/libft/ft_putstr_fd.c				\
				srcs/libft/ft_realloc.c					\
				srcs/libft/ft_split.c					\
				srcs/libft/ft_strchr.c					\
				srcs/libft/ft_strcat.c					\
				srcs/libft/ft_strlcpy.c					\
				srcs/libft/ft_strcmp.c					\
				srcs/libft/ft_strcpy.c					\
				srcs/libft/ft_strdup.c					\
				srcs/libft/ft_strjoin.c					\
				srcs/libft/ft_strlen.c					\
				srcs/libft/ft_strncmp.c					\
				srcs/libft/ft_strncpy.c					\
				srcs/libft/ft_strndup.c					\
				srcs/libft/ft_strsjoin.c				\
				srcs/libft/ft_strtok.c					\
				srcs/libft/ft_strtol.c					\
				srcs/libft/ft_strtrim.c					\
				srcs/libft/ft_substr.c					\
				srcs/libft/ft_memmove.c					\

OBJS		=	$(SRCS:.c=.o)

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g

LFLAGS		=	-lreadline

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(LFLAGS)
			@echo "\033[32m ~~ ./minishell successfully created! ~~"
			@echo "$$BIBOU"

clean:
			$(RM)
			rm -rf $(OBJS)
			@echo "\033[31m ~~ ./minishell successfully deleted! ~~"
			@echo "$$PQ"

fclean:		clean
			rm -rf $(NAME)
			@echo "\033[31m ~~ ./minishell successfully fdeleted! ~~"

re:			fclean all

.PHONY:		all clean fclean re

info: bibou
define BIBOU
           _       _     _          _ _ 
          (_)     (_)   | |        | | |
 _ __ ___  _ _ __  _ ___| |__   ___| | |
| '_ ` _ \| | '_ \| / __| '_ \ / _ \ | |
| | | | | | | | | | \__ \ | | |  __/ | |
|_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_|
endef
export BIBOU

info: pq
define PQ

 .--""--.___.._
(  <__>  )     `-.
|`--..--'|      <|      cleaning  ....
|       :|       /
|       :|--""-./
`.__  __;' 
    ""
endef
export PQ

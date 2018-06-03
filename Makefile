# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/02 12:01:32 by jle-quel          #+#    #+#              #
#    Updated: 2018/04/22 22:26:12 by hp               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = 21sh

FLAGS +=  -g3 -Wall -Wextra -I Includes #fsanitize=address -Ofast

SANITIZE += -g3 -fsanitize=address

SRC =	srcs/exec/exec.c\
		srcs/exec/redir.c\
		\
		srcs/init/init_std.c\
		srcs/init/main.c\
		srcs/init/signal.c\
		srcs/init/term.c\
		\
		srcs/builtins_env/env.c\
		srcs/builtins_env/builtins.c\
		srcs/builtins_env/cd.c\
		srcs/builtins_env/env_tools.c\
		srcs/builtins_env/buil_env.c\
		srcs/builtins_env/init_env.c\
		\
		srcs/lexer/lexer.c\
		srcs/lexer/list.c\
		srcs/lexer/lexer_id.c\
		srcs/lexer/lexer_tools.c\
		srcs/lexer/id_list.c\
		srcs/lexer/lexer_split.c\
		\
		srcs/ast/ast.c\
		srcs/ast/separator.c\
		srcs/ast/ast_tools.c\
		srcs/ast/priority.c\
		srcs/ast/ast_view.c\
		srcs/ast/redir_tools.c\
		srcs/ast/redir.c\
		srcs/ast/do_redir.c\
		\
		srcs/line_editing/check_d_quote.c\
		srcs/line_editing/check_nl.c\
		srcs/line_editing/d_quote.c\
		srcs/line_editing/eof_key.c\
		srcs/line_editing/keys_actions.c\
		srcs/line_editing/history/history_access.c\
		srcs/line_editing/history/history_list.c\
		srcs/line_editing/history/init_history.c\
		srcs/line_editing/history/line_history.c\
		srcs/line_editing/line_init.c\
		srcs/line_editing/line_operations.c\
		srcs/line_editing/line_paste.c\
		srcs/line_editing/line_refresh.c\
		srcs/line_editing/line_shortcuts.c\
		srcs/line_editing/line_tools.c\
		srcs/line_editing/line_tools_2.c\
		srcs/line_editing/list_adding.c\
		srcs/line_editing/list_deleting.c\
		srcs/line_editing/move_cursor.c\
		srcs/line_editing/move_cursor2.c\
		srcs/line_editing/print_editing_list.c\
		srcs/line_editing/prompt_mode.c\
		srcs/line_editing/readline.c\
		srcs/line_editing/refresh_stat.c\
		srcs/line_editing/replace_cursor.c\
		srcs/line_editing/visual_mode.c\
		\
		srcs/others/tools.c\
		\

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

LIBLOG = logger/liblogger.a

.PHONY = all clean fclean clean re

all: $(NAME)

$(OBJ): %.o: %.c
	@clang -c -I libft -I logger $(FLAGS) $< -o $@

$(LIBLOG):
	@make -C logger

$(LIBFT):
	@make -C libft

$(NAME): $(LIBLOG) $(LIBFT) $(OBJ)
	@clang $(OBJ) $(FLAGS) -I logger logger/liblogger.a -I libft $(LIBFT) -lncurses -o $(NAME)

fs: $(LIBFT) $(OBJ)
	@clang $(OBJ) $(FLAGS) -I logger logger/liblogger.a -I libft $(SANITIZE) $(LIBFT) -lncurses -o $(NAME)

clean:
	@rm -rf $(OBJ) objs graph graph.png
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@make -C logger fclean

re: fclean
	@make

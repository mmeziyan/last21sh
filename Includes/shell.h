/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 15:27:56 by juhallyn          #+#    #+#             */
/*   Updated: 2018/04/23 01:15:43 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <termios.h>
# include <termcap.h>
# include <stdio.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "libft.h"
# include "line_editing.h"
# include "lexer.h"
# include "ast.h"
# include "builtins_env.h"

//	DEBUG
# include "../logger/incs/logger.h"
// void	graph(t_ast *ast);

void					do_redirection(t_ast *parent, t_ast *left, t_ast *right);
/*
**  ----------------------------------------------------------------------------
**							--	STRUCTS --
**  ----------------------------------------------------------------------------
*/

/*
**	--			Master_stuct		--
**					(t_std)
*/

typedef struct			s_std
{
	struct winsize		win;
	struct s_history	*history;
	
	char				**path;
	// struct s_line		*line;
	struct s_lexer		*lexer;
	struct s_ast		*ast;
	struct s_line_stat	*stat;
	
	struct s_line		*line_list;
	struct s_line		*command_list;
	char				*line;
	// char				*command_str;

	char				*heredoc_line;
	char				*eof_str;

	char 				**myenv;
	int					nb_env;
	int					realfd[3];
	int					ret;
	bool				stdin;
}						t_std;

/*
**  ----------------------------------------------------------------------------
**							--	FUNCTIONS --
**  ----------------------------------------------------------------------------
*/

/*
**	--			Env functions		--
**					/ (BEGIN)
*/

/*
**	--	env.c --
*/

// char				**env_cpy(char **env);
// char				*find_env(char **env, char *var_name);

/*
**	--	setenv.c --
*/

// char				**add_variable(char *name, char *value, char **env);
// char				**modif_variable(char *name, char *value, char **env);
// void				ft_setenv(char *name, char *value, char ***env, int nb_arg);

/*
**	--			Env functions		--
**					(END) /
*/

/*
**	--	init_std.c --
*/

t_std				*std_singleton(t_std *std);
void				init_std(t_std **std);

/*
**	--	exec.c --
*/

int					execute_cmd(char *command);

/*
**	--	term.c --
*/

struct termios		*termios_sigleton(struct termios *term);
int					init_term_canon(bool canon);
// void				to_no_canonial(struct termios *term);
void				reset_term(struct termios *term);

/*
**	--	tools.c --
*/

void				ft_fatalexit(char *error);
int					ft_atoi_mod(char *str);
int					ft_ischar(int key);
void				ft_puterror(char *error);

/*
**	--	signal.c --
*/

void				ft_signal(void);
void				signal_handler(int sig);

int					builtins(t_ast *ast);


#endif

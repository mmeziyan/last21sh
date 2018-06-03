   /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpu <hpu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:47:45 by hpu               #+#    #+#             */
/*   Updated: 2018/04/22 02:24:41 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "shell.h"

# define LEFT 1
# define RIGHT 2

typedef enum		e_node_type
{
	OR,
	AND,
	SEMIC
}					t_node_type;

typedef struct			s_redir
{
	int					fd_out;
	int					fd_out_cpy;
	int					io_number;
	t_token				redir_type;
	int					fd_in;
	int					fd_file;
	struct s_redir		*next;
}						t_redir;


// typedef struct		s_cmd
// {
// 	char			*first;
// 	char			**argv;
// 	struct s_cmd	*next
// }					t_cmd;


typedef struct		s_ast
{
	t_token			type;
	t_lexer			*lexer_node;
	char			*data;
	
	char			**argv;
	int				ret;
	int				pid_pipe;
	struct s_ast	*parent;
	struct s_ast	*right;
	struct s_ast	*left;
}					t_ast;

int		ft_creat_file(char *file, t_token type, int info);

/*
**	--	ast.c --
*/

t_ast		*process(t_lexer *lexer, t_ast *parent, int info);
// void		do_redir();
// void		struct_redir_destroy(void);
/*
**	--	exec.c --
*/

char		**cmd_create(t_lexer *lexer_node);
int			exec(t_ast *ast);

/*
**	--	separator.c --
*/

t_ast		*operators(t_lexer *lexer, t_lexer *new_separator, t_ast *dad);

/*
**	--	do_redir.c --
*/

void	do_redir(void);

/*
**	--	redir.c --
*/

int		new_redirection(t_lexer *cmd);

/*
**	--	redir_tools.c --
*/

t_redir		*grep_head(t_redir *new, bool replace);
void		struct_redir_destroy(void);
t_redir		*new_redir_node(t_redir data);
t_lexer		*redir_io_number(t_lexer *cmd, t_redir *redir);
t_redir		t_redir_init(void);


/*
**	--	ast_tools.c --
*/

t_lexer		*move_to_end(t_lexer *separator, int info);
t_lexer		*priority(t_ast *parent, int info);

/*
**	--	ast_tools.c --
*/

t_ast		*new_node(t_lexer *node, t_ast *parent);
void		free_ast(t_ast **ast);
int			is_operator(t_lexer *lex);

char		*lexer_to_str(t_lexer *token);

/*
**	--	ast_view.c --
*/

void		graph(t_ast *ast);

#endif

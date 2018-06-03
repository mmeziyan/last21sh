/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hp <hp@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 01:07:21 by hp                #+#    #+#             */
/*   Updated: 2018/04/23 23:06:03 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_ast *ft_semicolon(t_lexer *lexer, t_ast *dad, t_lexer *new_separator)
{
    t_ast *new;

    new = new_node(new_separator, dad);
    if (new_separator->prev)
	{
		new->left = process(lexer, new, 1);
		if (new->left)
			new->ret = new->left->ret;
	}
	if (!new->left)
    	ft_puterror("syntax error near unexpected token ';'");
    if (new_separator->next)
    {
		new->right = process(lexer, new, 2);
		if (new->right)
			new->ret = new->right->ret;
	}
    return (new);
}

static t_ast *ft_and(t_lexer *lexer, t_ast *dad, t_lexer *new_separator)
{
    t_ast *new;

    new = new_node(new_separator, dad);
    new->ret = 1;
	if (!new_separator->prev || !new_separator->next)
	{
		ft_puterror("syntax error near unexpected token '&&'");
		return (new);
	}
    if (new_separator->prev)
        new->left = process(lexer, new, 1);
    if (new_separator->next && new->left && new->left->ret == 0)
    {
        if ((new->right = process(lexer, new, 2)) && new->right->ret == 0)
			new->ret = 0;
    }
    return (new);
}

static t_ast *ft_or(t_lexer *lexer, t_ast *dad, t_lexer *new_separator)
{
    t_ast *new;

    new = new_node(new_separator, dad);
	if (!new_separator->prev || !new_separator->next)
	{
		ft_puterror("syntax error near unexpected token '||'");
		return (new);
	}
    if (new_separator->prev)
    {
        new->left = process(lexer, new, 1);
        if ((new->ret = new->left->ret) == 0)
            return (new);
    }
    if (new_separator->next)
    {
        new->right = process(lexer, new, 2);
        new->ret = new->right->ret;
    }
    return (new);
}

static t_ast *ft_pipe(t_lexer *lexer, t_ast *dad, t_lexer *new_separator)
{
	t_ast	*new;
	int		pfd[2];
	int		status; 
	int		tmp;
	int		pid;

	new = new_node(new_separator, dad);
	tmp = dup(0);
	if (pipe(pfd) == -1)
	{
		ft_puterror("pipe failed\n");
		return (new);
	}   
	if ((pid = fork()) < 0)
	{
		ft_puterror("fork failed\n");
		return (new);
	}
	if (pid == 0)
	{
        close(pfd[0]); /* close the unused read side */
        dup2(pfd[1], 1); /* connect the write side with stdout */
        close(pfd[1]); /* close the write side */
        if (!(new->left = process(lexer, new, 3)))
			ft_fatalexit("21sh: syntax error: unexpected '|'"); 
		exit (0); 
	}
	else
	{
        close(pfd[1]); /* close the unused write side */
        dup2(pfd[0], 0); /* connect the read side with stdin */
        close(pfd[0]); /* close the read side */
        waitpid(pid, &status, WUNTRACED | WCONTINUED);
        if (!(new->right = process(lexer, new, 4)))
        	ft_puterror("21sh: syntax error: unexpected '|'");
        dup2(tmp, 0);
        return (new);
    }
}

t_ast *operators(t_lexer *lexer, t_lexer *new_separator, t_ast *dad)
{
    t_ast *new;
    
	new_separator->status = 1;
    new = NULL;
	
    if (new_separator->type == SEMICOLON)
        new = ft_semicolon(lexer, dad, new_separator);
    if (new_separator->type == T_AND)
        new = ft_and(lexer, dad, new_separator);
    if (new_separator->type == T_OR)
        new = ft_or(lexer, dad, new_separator);
    if (new_separator->type == PIPE)
        new = ft_pipe(lexer, dad, new_separator);
    return (new);
}

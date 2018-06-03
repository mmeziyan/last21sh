/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hp <hp@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:30:07 by hp                #+#    #+#             */
/*   Updated: 2018/04/23 22:49:01 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//.H
/* ************************************************************************** */

// typedef struct			s_redir
// {
// 	int					fd_out;
// 	int					fd_out_cpy;
// 	t_token				redir_type;
// 	int					fd_in;
// 	struct s_redir		*next;
// }						t_redir;

//LIBFT
/* ************************************************************************** */

// static char	*ft_justnum(char *str)
// {
// 	int		n;

// 	n = -1;
// 	while (str[++n])
// 	{
// 		if (!ft_isdigit(str[n]))
// 			return (str + n);
// 	}
// 	return (NULL);
// }

// STUCT T_REDIR
/* ************************************************************************** */


// static t_redir *new_redir_node(t_redir data)
// {
// 	t_redir *new;

// 	if (!(new = malloc(sizeof(t_redir))))
// 		ft_fatalexit("malloc error");
// 	new->fd_out = data.fd_out;
// 	new->redir_type = data.redir_type;
// 	new->fd_in = data.fd_in;
// 	new->fd_out_cpy = -1;
// 	new->next = NULL;
// 	return (new);
// }

// void	struct_redir_destroy(void)
// {
// 	t_redir *to_destroy;
// 	t_redir *tmp;
// 	t_std	*std;

// 	std = std_singleton(NULL);
// 	to_destroy = grep_head(NULL, false);
// 	while (to_destroy)
// 	{
// 		tmp = to_destroy;
// 		to_destroy = to_destroy->next;
// 		dup2(tmp->fd_out_cpy, tmp->fd_out);
// 		close(tmp->fd_out_cpy);
// 		free(tmp);
// 	}
// 	grep_head(NULL, true);
// }

// static	void	replace_fd(t_redir *prev, t_redir *head, t_redir data)
// {
// 	t_redir		*new;

// 	new = new_redir_node(data);
// 	if (head->fd_in > 2)
// 		close(head->fd_in);
// 	free(head);
// 	if (prev == NULL)
// 	{	
// 		if (head->next)
// 		{
// 			head = grep_head(head->next, true);
// 			head->next = new;
// 		}
// 		else
// 			grep_head(new, true);
// 	}
// 	else
// 		prev->next = new;
// }

// static	void	search_replace_fd(t_redir data)
// {
// 	t_redir		*head;
// 	t_redir		*prev;

// 	if (!(head = grep_head(NULL, false)))
// 	{
// 		head = new_redir_node(data);
// 		grep_head(head, true);
// 		return ;
// 	}
// 	prev = NULL;
// 	while (42)
// 	{
// 		if (head->fd_out == data.fd_out)
// 		{
// 			replace_fd(prev, head, data);
// 			return ;
// 		}
// 		if (!head->next)
// 		{
// 			head->next = new_redir_node(data);
// 			return ;
// 		}
// 		prev = head;
// 		head = head->next;
// 	}
// }

// STUCT T_REDIR
/* ************************************************************************** */

// static int		command_clean(t_ast *ast, t_lexer *cmd)
// {
// 	while (cmd && cmd->status != 1)
// 	{
// 		if (cmd->type == REDIR_SUP || cmd->type == D_REDIR_SUP || cmd->type == REDIR_INF || cmd->type == D_REDIR_INF)

// 	}	
// }




// static t_lexer *redir_ampersand(t_lexer *cmd, t_redir *redir)
// {
// 	if (cmd->next && cmd->next->type == STD_SEPARATOR)
// 		cmd = cmd->next;
// 	if (!cmd->next)
// 	{
// 		my_printf("21sh: syntax error: unexpected 'newline'\n", 2, cmd->data);
// 		return (NULL);
// 	}
// 	if (cmd->next && ft_strcmp(cmd->next->data, "-\0") == 0 
// 	&& cmd->type != REDIR_INF)
// 	{
// 		cmd = cmd->next;
// 		redir->fd_in = open("/dev/null", O_WRONLY);
// 		search_replace_fd(*redir);
// 		return (cmd->next ? cmd->next : cmd);
// 	}
// 	if (cmd->next && cmd->next->type == WORD)
// 	{	 
// 		cmd = cmd->next;
// 		if (ft_justnum(cmd->data) || ft_strlen(cmd->data) != 1)
// 		{
// 			my_printf("21sh: %s bad file descriptor\n", 2, cmd->data);
// 			return (NULL);
// 		}
// 		else if ((redir->fd_in = ft_atoi(cmd->data)) != redir->fd_out)
// 			search_replace_fd(*redir);
// 	}
// 	return (cmd->next ? cmd->next : cmd);
// }

// static t_lexer *redir_io_number(t_lexer *cmd, t_redir *redir)
// {
// 	if (cmd->prev && cmd->prev->type == IO_NUMBER)
// 		redir->fd_out = ft_atoi(cmd->prev->data);
// 	else
// 	{
// 		if (cmd->type == REDIR_INF || cmd->type == D_REDIR_INF)
// 			redir->fd_out = 0;
// 		if (cmd->type == REDIR_SUP || cmd->type == D_REDIR_SUP)
// 			redir->fd_out = 1;
// 	}
// }

// static t_redir		t_redir_init(void)
// {
// 	t_redir redir;

// 	redir.redir_type = -1;
// 	redir.fd_in = -1;
// 	redir.fd_out = -1;
// 	redir.fd_out_cpy = -1;
// 	return (redir);
// }

// static t_lexer		*redirection(t_lexer *cmd)
// {
// 	t_redir		redir;

// 	redir = t_redir_init();
// 	redir.redir_type = cmd->type;
// 	redir_io_number(cmd, &redir);
// 	if (cmd->next && cmd->next->type == AMPERSAND && cmd->type != D_REDIR_INF)
// 		return (redir_ampersand(cmd->next, &redir));
// 	if (cmd->next && cmd->next->type == STD_SEPARATOR)
// 		cmd = cmd->next;
// 	if (cmd->next && cmd->next->type == WORD 
// 	&& ft_strcmp(cmd->next->data, "-\0") != 0)
// 	{
// 		cmd = cmd->next;
// 		if ((redir.fd_in = 
// 		ft_creat_file(cmd->data, redir.redir_type, 1)) == -1)
// 		{
// 			log_fatal("cannot open fd %i", cmd->data);
// 			return (NULL); // else access denied
// 		}
// 	}
// 	search_replace_fd(redir);
// 	return (cmd);
// }

// static int		new_redirection(t_ast *ast, t_lexer *cmd)
// {
// 	t_redir		redir;

// 	lexer_clean_redir(cmd);
// 	while (cmd && cmd->status != 1)
// 	{
// 		redir = t_redir_init();
// 		if (cmd->type == REDIR_SUP || cmd->type == D_REDIR_SUP 
// 		|| cmd->type == REDIR_INF || cmd->type == D_REDIR_INF)
// 			if (!(cmd = redirection(cmd)))
// 				return (-1);
// 		cmd = cmd->next;
// 	}
// 	return (0);
// }

// void	do_redir(void)
// {
// 	t_redir		*head;

// 	head = grep_head(NULL, false);
// 	while (head)
// 	{
// 		head->fd_out_cpy = dup(head->fd_out);
// 		head = head->next;
// 	}
// 	head = grep_head(NULL, false);
// 	while(head)
// 	{
// 		if (head && head->fd_out == -1)
// 		{
// 			my_printf("21sh : %i: Bad file descriptor\n", 2, head->fd_out);
// 			return ;
// 		}	
// 		dup2(head->fd_in, head->fd_out);
// 		if (head->fd_in > 2)
// 			close (head->fd_in);
// 		head = head->next;
// 	}
// }

//DEBUG
/* ************************************************************************** */

void	put_fd_struct_logger(void)
{
	t_redir *head = grep_head(NULL, false);

	while (head)
	{
		log_fatal("fd_out = %i", head->fd_out);
		log_fatal("fd_out_cpy = %i", head->fd_out_cpy);
		log_fatal("redir_type = %i", head->redir_type);
		log_fatal("fd_in = %i", head->fd_in);
		log_fatal("io_number = %i", head->io_number);
		log_success("");
		head = head->next;
	}
}

//PRINCIPAL FONCTION
/* ************************************************************************** */

static t_ast	*words(t_lexer *word, t_ast *parent)
{
	t_ast 	*new;

	new = NULL;
	// ft_putendl("1--");
	while (word->prev && word->prev->status != 1)
		word = word->prev;
	if (word->type == STD_SEPARATOR && word->next && word->next->status != 1)
		word = word->next;	
	new = new_node(word, parent);
	new->type = WORD;
	// ft_putendl("2--");
	if ((new_redirection(new->lexer_node)) == -1)
	{
		new->ret = -1;
		return (new);
	}
	// ft_putendl("3--");
	new->argv = cmd_create(word);
	put_fd_struct_logger();
	do_redir();	
	new->ret = new->argv[0] ? exec(new) : 0;
	struct_redir_destroy();
	return (new);
}


t_ast	*process(t_lexer *lexer, t_ast *parent, int info)
{
	// t_ast 	*new;
	t_lexer *operator;

	// new = NULL;
	operator = priority(parent, info);
	if (is_operator(operator) == 0)
		return (operators(lexer, operator, parent));
	else if (operator)
	{
		return (words(operator, parent));
		// while (operator->prev && operator->prev->status != 1)
		// 	operator = operator->prev;
		// if (operator->type == STD_SEPARATOR && operator->next && operator->next->status != 1)
		// 	operator = operator->next;	
		// new = new_node(operator, parent);
		// new->type = WORD;
		// if ((new_redirection(new->lexer_node)) == -1)
		// {
		// 	new->ret = -1;
		// 	return (new);
		// }
		// new->argv = cmd_create(operator);
		// put_fd_struct_logger();
		// do_redir();	
		// new->ret = new->argv[0] ? exec(new) : 0;
		// struct_redir_destroy();
	}
	return (NULL);
}

#include "shell.h"

static char	*ft_justnum(char *str)
{
	int		n;

	n = -1;
	while (str[++n])
	{
		if (!ft_isdigit(str[n]))
			return (str + n);
	}
	return (NULL);
}

static	void	replace_fd(t_redir *prev, t_redir *head, t_redir data)
{
	t_redir		*new;

	new = new_redir_node(data);
	if (head->fd_in > 2)
		close(head->fd_in);
	free(head);
	if (prev == NULL)
	{	
		if (head->next)
		{
			head = grep_head(head->next, true);
			head->next = new;
		}
		else
			grep_head(new, true);
	}
	else
		prev->next = new;
}

static	int	search_replace_fd(t_redir data)
{
	t_redir		*head;
	t_redir		*prev;

	head = grep_head(NULL, false);
	
	while(head && data.fd_in < -2)
	{
		// my_printf("%i == %i\n", 1, head->io_number, -data.fd_in);
		if (head->io_number == -data.fd_in)
			data.fd_in = head->fd_in;
		head = head->next;
	}
	if (data.fd_in < -2)
		return (-1);
	if (!(head = grep_head(NULL, false)))
	{
		head = new_redir_node(data);
		grep_head(head, true);
		return (1);
	}
	prev = NULL;
	head = grep_head(NULL, false);
	while (42)
	{
		if (head->fd_out == data.fd_out && data.fd_out > 0)
		{
			replace_fd(prev, head, data);
			return (1);
		}
		if (!head->next)
		{
			head->next = new_redir_node(data);
			return (1);
		}
		prev = head;
		head = head->next;
	}
}

static void		lexer_clean_redir(t_lexer *cmd)
{
	while (cmd && cmd->status != 1)
	{
		if (cmd->type == REDIR_SUP || cmd->type == D_REDIR_SUP 
		|| cmd->type == REDIR_INF || cmd->type == D_REDIR_INF)
		{
			cmd->status = 2;
			if (cmd->prev && (cmd->prev->type == STD_SEPARATOR 
			|| cmd->prev->type == IO_NUMBER))
				cmd->prev->status = 2;
			if (cmd->next && cmd->next->type == AMPERSAND)
			{
				cmd = cmd->next;
				cmd->status = 2;
			}
			if (cmd->next && cmd->next->type == STD_SEPARATOR)
			{
				cmd = cmd->next;
				cmd->status = 2;
			}
			if (cmd->next && cmd->next->type == WORD)
			{
				cmd = cmd->next;
				cmd->status = 2;
			}
		}
		cmd = cmd->next;
	}
}

static t_lexer *redir_ampersand(t_lexer *cmd, t_redir *redir)
{
	// ft_putendl("1--");
	if (cmd->next && cmd->next->type == STD_SEPARATOR)
		cmd = cmd->next;
	// ft_putendl("2--");
	if (!cmd->next)
	{
		my_printf("21sh: syntax error: unexpected 'newline'\n", 2, cmd->data);
		return (NULL);
	}
	// ft_putendl("3--");
	if (cmd->next && ft_strcmp(cmd->next->data, "-\0") == 0 
	&& cmd->type != REDIR_INF)
	{
		cmd = cmd->next;
		redir->fd_in = open("/dev/null", O_WRONLY);
		search_replace_fd(*redir);
		return (cmd->next ? cmd->next : cmd);
	}
	// ft_putendl("4--");
	if (cmd->next && cmd->next->type == WORD)
	{	 
		cmd = cmd->next;
		if (ft_justnum(cmd->data) || ft_strlen(cmd->data) != 1)
		{
			my_printf("21sh: %s bad file descriptor\n", 2, cmd->data);
			return (NULL);
		}
		// ft_putendl("5--");
		// else
			// ft_creat_file(cmd->data, redir.redir_type, 1)) == -1)
		else if ((redir->fd_in = ft_atoi(cmd->data)) != redir->fd_out)
		{
			// ft_putendl("hola");
			redir->fd_in = redir->fd_in > 2 ? -redir->fd_in : redir->fd_in;
			// ft_putendl("6--");
			// ft_putnbr(redir->fd_in);
			if ((search_replace_fd(*redir)) == -1)
			{
				
				my_printf("21sh : %i: Bad file descriptor\n", 2, redir->fd_in);
				struct_redir_destroy();
				return (NULL);
			}
		}
		// ft_putendl("7--");
	}
	return (cmd->next ? cmd->next : cmd);
}

static t_lexer		*redirection(t_lexer *cmd)
{
	t_redir		redir;
	// ft_putendl("1--");
	redir = t_redir_init();
	redir.redir_type = cmd->type;
	// ft_putendl("2--");
	redir_io_number(cmd, &redir);
	// ft_putendl("3--");
	if (cmd->next && cmd->next->type == AMPERSAND && cmd->type != D_REDIR_INF)
		return (redir_ampersand(cmd->next, &redir));
	// ft_putendl("4--");
	if (cmd->next && cmd->next->type == STD_SEPARATOR)
		cmd = cmd->next;
	if (cmd->next && cmd->next->type == WORD 
	&& ft_strcmp(cmd->next->data, "-\0") != 0)
	{
		// ft_putendl("5--");
		cmd = cmd->next;
		if ((redir.fd_in = 
		ft_creat_file(cmd->data, redir.redir_type, 1)) == -1)
			return (NULL); // else access denied
		// ft_putendl("6--");
	}
	
	search_replace_fd(redir);
	// ft_putendl("7--");
	return (cmd);
}

// line_editing(int cmd_return)

char			*here_doc(void)
{
	// // t_line	*edit_line;
	// t_std	*std;
	// // char	*command;

	// // command = NULL;
	// std = std_singleton(NULL);
	// // std = std_singleton(NULL);
	// std->stat = init_line_stat();
	// std->line = init_line('\0');
	// // edit_line = init_line('\0');
	// // std->line = edit_line;
	// // ft_putstr_fd("\n", 0);

	// std->stat->prompt_mode = PROMPT_HEREDOC;
	// // prompt_size = 7;
	// print_prompt(0, PROMPT_HEREDOC, \
	// std->win.ws_col - 8);
	// // command = 
	// readline(&std->line);

	// // if (command != NULL)
	// 	// return (command);
	// return (NULL);
}

int		new_redirection(t_lexer *cmd)
{
	t_redir		redir;

	lexer_clean_redir(cmd);
	while (cmd && cmd->status != 1)
	{
		redir = t_redir_init();
		if (cmd->type == REDIR_SUP || cmd->type == D_REDIR_SUP 
		|| cmd->type == REDIR_INF)
			if (!(cmd = redirection(cmd)))
				return (-1);
		if (cmd->type == D_REDIR_INF)
		{
			if (cmd->next && cmd->next->type == STD_SEPARATOR)
				cmd = cmd->next;
			if (cmd->next && cmd->next->type == WORD)
				std_singleton(NULL)->eof_str = cmd->next->data;
			// ft_putendl(std_singleton(NULL)->eof_str);
			// init_term_canon(false);
			here_doc();
			// init_term_canon(true);
			
			// ft_putendl(line_editing(2));
		}
		cmd = cmd->next;
	}
	return (0);
}


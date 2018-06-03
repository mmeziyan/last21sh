/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 20:22:38 by juhallyn          #+#    #+#             */
/*   Updated: 2018/03/15 18:19:41 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				join_line(char *command, t_line **j_line)
{
	size_t		i;

	i = 0;
	if (!*j_line)
		*j_line = init_line('\0');
	if (!command)
	{
		add_end(j_line, NEWLINE_ANSI);
		add_end(j_line, '\n');
		return ;
	}
	else
	{
		while (command[i])
		{
			add_end(j_line, command[i]);
			i++;
		}
	}
	add_end(j_line, NEWLINE_ANSI);
	add_end(j_line, '\n');
}

int					write_prompt(int prompt_mode)
{
	if (prompt_mode == PROMPT_STANDARD)
	{
		print_prompt(0, PROMPT_STANDARD, std_singleton(NULL)->win.ws_col - 7);
	}
	else if (prompt_mode == PROMPT_ERR)
	{
		print_prompt(-1, PROMPT_STANDARD, std_singleton(NULL)->win.ws_col - 7);
	}
	else if (prompt_mode == PROMPT_QUOTE)
	{
		print_prompt(0, PROMPT_QUOTE, std_singleton(NULL)->win.ws_col - 7);
	}
	else if (prompt_mode == PROMPT_DQUOTE)
	{
		print_prompt(0, PROMPT_DQUOTE, std_singleton(NULL)->win.ws_col - 8);
	}
	else if (prompt_mode == PROMPT_HEREDOC)
	{
		print_prompt(0, PROMPT_HEREDOC, std_singleton(NULL)->win.ws_col - 9);
	}
	return (0);
}

static inline int	prompt_err(t_line_stat **stat, t_line **edit_line)
{
	// char	*line;

	// line = NULL;
	// line = list_to_str(std->line_list, true);
	// ft_strdel(&line);
	ft_putstr_fd("\n", 0);
	*edit_line = init_line('\0');
	reset_stat(stat, PROMPT_STANDARD);
	init_prompt_size(*stat);
	return (PROMPT_ERR);
}

// int		prompt_heredoc(t_line **edit_line, t_line **j_line)
// {
// 	t_std	*std;
// 	int		prompt;

// 	std = std_singleton(NULL);
// 	// reset_stat(stat, prompt);
// 	*edit_line = init_line('\0');
// 	std->command_line = list_to_str(j_line, false);
// 	log_debug("pop");
// 	log_debug(list_to_str(j_line, false));
// 	return (1);
// 	//  if (!*j_line)
// 		// join_line(std->command_line, j_line);
// 	// if (std->command_line)
// 		// ft_strdel(&std->command_line);
// 	// std->command_line = list_to_str(j_line, false);
// 	// std->line = *edit_line;
// 	// init_prompt_size(*stat);
// 	// return (prompt);
// }

int					prompt_mode(t_line_stat **stat, t_line **edit_line)
{
	// t_std			*std;
	// int				ret_quote;
	// int				mode;
	// static t_line	*j_line = NULL;

	// std = std_singleton(NULL);
	// mode = (*stat)->prompt_mode;
	// if ((*stat)->prompt_mode == PROMPT_ERR)
	// 	return (prompt_err(stat, edit_line));
	// // if ((*stat)->prompt_mode == PROMPT_HEREDOC)
	// 	// log_debug(std->command_line);
	// 	// prompt_heredoc(edit_line,&j_line);
	// ret_quote = init_ret_quote(mode, edit_line, &j_line);
	// if (ret_quote == 0)
	// {
	// 	reset_stat(stat, PROMPT_STANDARD);
	// 	if (j_line && mode != PROMPT_STANDARD)
	// 	{
	// 		std->command_line = list_to_str(&j_line, true);
	// 		std->command_line[ft_strlen(std->command_line) - 2] = '\0';
	// 	}
	// 	add_to_history(std->command_line, *stat);
	// 	init_prompt_size(*stat);
	// 	return (PROMPT_STANDARD);
	// }
	
	// if (ret_quote == CHAR_QUOTE || ret_quote == CHAR_DQUOTE)
	// 	return (line_d_quote(ret_quote, edit_line, &j_line, stat));
	// return (PROMPT_STANDARD);
}

void				init_prompt_size(t_line_stat *stat)
{
	t_std	*std;

	std = std_singleton(NULL);
	if (std->win.ws_col >= stat->prompt_size && stat->prompt_size < 7)
	{
		if (stat->prompt_mode == PROMPT_STANDARD
		|| stat->prompt_mode == PROMPT_QUOTE)
			stat->prompt_size = 7;
		if (stat->prompt_mode == PROMPT_DQUOTE)
			stat->prompt_size = 8;
	}
	if (std->win.ws_col <= stat->prompt_size || (std->win.ws_col == 6)
	|| (std->win.ws_col == 7) || (std->win.ws_col == 8) || std->win.ws_col == 9)
		stat->prompt_size = 0;
}

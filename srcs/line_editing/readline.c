/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:40:54 by juhallyn          #+#    #+#             */
/*   Updated: 2018/04/21 17:37:15 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool read_line(void)
{
	char			*str_key;
	int				key;
	t_std			*std;

	std = std_singleton(NULL);
	while (42)
	{
		if (!(str_key = (char *)ft_memalloc(sizeof(char) * 9)))
			return (NULL);
		// log_debug("2");
		if (read(0, str_key, (sizeof(char) * 8)) > 0)
		{
			key = ft_atoi_mod(str_key);
			// paste_mod(str_key, &std->line_list , std->stat);
			ft_strdel(&str_key);
			// log_success("koko");
			if (ft_edit_line(NULL, NULL, key) == 0)
			{
				if (std->line)
					ft_strdel(&std->line);
				std->line = list_to_str(&std->command_list, true);	
				log_success("std->line = %s", std->line);
				// if ft_strdel(&std->line);
				return (true);
			}
			
			// log_debug("6");
			// log_debug("3");
		}
		else
			read_err_free(&std->stat, str_key);
	}
	return (false);
}

char			*line_editing(int cmd_return)
{
	// t_line	*edit_line;
	t_std	*std;
	// char	*command;
	// log_debug("1");
	std = std_singleton(NULL);
	std->stat = init_line_stat();
	
	// edit_line = init_line('\0');
	
	std->line_list = init_line('\0');
	
	write_prompt(std->ret == 0 ? PROMPT_STANDARD : PROMPT_ERR);
	
	// read_line();
	free(std->stat);
	log_trace("--------end read_line-------------");
	
	// log_debug(list_to_str(&std->command_list, true));
	// exit (-1);
	// command = NULL;
	// edit_line = init_line('\0');
	// std->line = edit_line;
	// std->line = init_line('\0');
	// ft_putstr_fd("\n", 0);
	// print_prompt(cmd_return, PROMPT_STANDARD, 
	// std->win.ws_col - PROMPT_SIZE);
	// command = readline(&std->line);
	// if (command != NULL)
	// return (std->line_str);
	return (NULL);
}

static char		*readline_process(t_line **edit_line, t_line_stat **stat)
{
	char			*str_key;
	int				prompt_mode;
	int				key;

	while (42)
	{
		if (!(str_key = (char *)ft_memalloc(sizeof(char) * 9)))
			return (NULL);
		if (read(0, str_key, (sizeof(char) * 8)) > 0)
		{

			// key = 0;
			key = ft_atoi_mod(str_key);
			// // log_trace("key = %i", key);
			// // log_debug("key = %i", );
			paste_mod(str_key, edit_line, *stat);
			ft_edit_line(edit_line, *stat, key);


			// if ((prompt_mode = ft_edit_line(edit_line, *stat, key)) == -2)
			// {
			// 	ft_putendl("");
			// 	return (NULL);
			// }
			// ft_strdel(&str_key);
			// // init_term_canon(true);
			// if (write_prompt(prompt_mode) == PROMPT_STANDARD)
			// {
			// 	// if ()
			// 	return (NULL);
			// 	// ft_strdel(&str_key);
			// 	// return (std_singleton(NULL)->command_line);
			// }
			// // ft_strdel(&str_key);
		}
		else
			read_err_free(stat, str_key);
	}
	return (NULL);
}

char			*readline(t_line **edit_line)
{
	// char			*command;
	// t_line_stat		*stat;

	
	// stat.prompt_mode = PROMPT_HEREDOC;
	// prompt_size = 7;
	// command = 
	// readline_process(edit_line, &(std_singleton(NULL)->stat));
	// free(std_singleton(NULL)->stat);
	// return (std_singleton(NULL)->command_line);
}

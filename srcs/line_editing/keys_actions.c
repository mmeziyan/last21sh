// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 12:54:39 by juhallyn          #+#    #+#             */
/*   Updated: 2018/03/20 11:57:21 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static inline int	switch_key_extended(t_line **edit_line, t_line_stat *stat,\
					int key)
{
	// if (key == ALT_SUP)
		// go_to_next_word(edit_line, stat);
	// else if (key == ALT_INF || key == CTRL_INF_XTERM)
		// go_to_back_word(edit_line, stat);
	if (key == ALT_RIGHT)
	{
		go_to_next_word(edit_line, stat);
		go_to_next_word(edit_line, stat);
	}
	// if (key == ALT_C)
	// {
		// go_to_next_word(edit_line, stat);
		// go_to_next_word(edit_line, stat);
	// }
	else if (key == ALT_LEFT)
	{
		go_to_back_word(edit_line, stat);
		go_to_back_word(edit_line, stat);
	}
	return (0);
}

static inline int	switch_key(t_line **edit_line, t_line_stat *stat, int key)
{
	if (ft_ischar(key) != 0)
		insertion(stat, edit_line, key);
	else if (key == DEL)
		del_delete(stat, edit_line);
	else if (key == SIZE_CHANGED || key == CTRL_L)
		refresh_line(stat);
	else if (key == LEFT_ARROW)
		move_left(stat);
	else if (key == RIGHT_ARROW && (stat->nb_char > stat->cursor_index))
		move_right(stat);
	else if (key == UP_ARROW)
		read_history_up(edit_line, stat);
	else if (key == DOWN_ARROW)
		read_history_down(edit_line, stat);
	else if (key == BACKSPACE)
		backspace_delete(stat, edit_line);
	else if (key == HOME || key == HOME_SCREEN)
		move_begin(*edit_line, stat);
	else if (key == END || key == END_SCREEN)
		move_end(*edit_line, stat);
	else
		switch_key_extended(edit_line, stat, key);
	return (1);
}

// int					hh(t_line_stat **stat, t_line **edit_line)
// {
// 	t_std			*std;
// 	int				ret_quote;
// 	int				mode;
// 	static t_line	*j_line = NULL;

// 	std = std_singleton(NULL);
// 	if (!std->heredoc_line)
// 	{
// 		std->heredoc_line = list_to_str(edit_line, false);
// 		if (!j_line)
// 			join_line(std->heredoc_line, &j_line);
// 		std->heredoc_line = list_to_str(&j_line, false);
// 		// std->heredoc_line = list_to_str(edit_line, true);
// 		log_debug(std->heredoc_line);
// 	}
// 	if (ft_strcmp(std->heredoc_line, std->eof_str) == 0)
// 	{
// 		log_debug("ok");
// 		return (-2);
// 		// reset_stat(stat, PROMPT_STANDARD);
// 		// if (j_line && mode != PROMPT_STANDARD)
// 		// {
// 		// std->command_line = list_to_str(&j_line, true);
// 		// std->heredoc_line[ft_strlen(std->heredoc_line) - 2] = '\0';
// 		// }
// 		// add_to_history(std->command_line, *stat);
// 		// init_prompt_size(*stat);
// 		// return (PROMPT_STANDARD);
// 	}
// 	// ft_strdel(&std->heredoc_line);
// 	// if (ret_quote == CHAR_QUOTE || ret_quote == CHAR_DQUOTE)
// 		// return (line_d_quote(ret_quote, edit_line, &j_line, stat));
// 	return (PROMPT_HEREDOC);
// }

int					ft_edit_line(t_line **edit_line, t_line_stat *stat, int key)
{
	t_std	*std;
	int		ret_quote;

	ret_quote = 0;
	std = std_singleton(NULL);
	std->stat->win_index = std->stat->prompt_size + std->stat->cursor_index;
	if (key == ENTER)
	{
		// move_end(*line_list, stat);
		// return (1);
		// // if ()
		// // std->line_list
		// std->line_str = list_to_str(&std->line_list, false);
		// if (std->eof_str)
		// {
			// std->line_str = list_to_str(&std->line_list, true);
		// 	if (ft_strcmp(std->eof_str, std->line_str) == 0)
		// 	{
		// 		return (0);
		// 	}
		// 	write_prompt(PROMPT_HEREDOC);
		// 	return (PROMPT_HEREDOC);
		// 	// ft_strjoin(std->command_line, std->line_str);
		// 


		// free_list(&std->line_list, true);


		if (std->line)
			ft_strdel(&std->line);
		if (!std->command_list)
		{
			// std->command_list = init_line('\0');
			std->command_list = std->line_list;
			// std->line = list_to_str(&std->line_list, false);
		}
		else
		{
			std->line = list_to_str(&std->line_list, true);
			join_line(std->line, &std->command_list);
		}
		if ((ret_quote = check_close_d_quote(std->command_list)) != 0)
		{
			write_prompt(ret_quote == CHAR_DQUOTE
			? PROMPT_DQUOTE : PROMPT_QUOTE);
			reset_stat(&std->stat, ret_quote == CHAR_DQUOTE
			? PROMPT_DQUOTE : PROMPT_QUOTE);
			
			std->line_list = init_line('\0');	
		}
		// free_list(&std->line_list);

		// ret_quote = 0;

		// log_debug("ret_quote = %i", ret_quote);	
		// log_debug("2");
		// log_debug("3");
		
		// std->line = list_to_str(&std->line_list, true);
		
		// init_prompt_size(std->stat);
		// log_debug("4");
		
		// log_debug("5");
		// reset_stat(std->stat, PROMPT_STANDARD);
		// log_debug(list_to_str(&std->line_list, false));
		// join_line(std->line_str, &std->command_list);
		// // join_line(std->line, edit_line);
		// 	// return (ret_quote);
		// // log_debug(std->line);
		// // if (stat->prompt_mode == PROMPT_HEREDOC)
		// 	// ret_quote = hh(&stat, edit_line);// ret_quote = 1; 
			
		// // else
		// 	// ret_quote = prompt_mode(&stat, edit_line);
		// // log_debug("1");
		// // ret_quote = prompt_mode(&stat, edit_line);
		return (ret_quote);
	}
	if (key == PROMPT_ERR)
	{
		move_end(std->line_list, stat);
		std->ret = -1;
		// stat->prompt_mode = PROMPT_ERR;
		// return (prompt_mode(&stat, edit_line));
	}

	if (key == CTRL_D)
		eof_key(&std->line_list, std->stat);
	// log_debug("4");
	else if (key == SIZE_CHANGED || key == CTRL_L)
		refresh_line(std->stat);
	else
		return (switch_key(&std->line_list, std->stat, key));
	return (-1);
}

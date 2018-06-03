/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:56:14 by julien            #+#    #+#             */
/*   Updated: 2018/03/15 18:18:09 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	bool		newline_at_left(t_line_stat *stat)
{
	t_std	*std;
	t_line	*tmp;

	tmp = NULL;
	std = NULL;
	std = std_singleton(NULL);
	if (std && std->line && stat->cursor_index)
		tmp = move_list_to_cursor(&std->line_list, stat->cursor_index);
	if (tmp && tmp->c == '\n' && tmp->prev && tmp->prev->c == NEWLINE_ANSI)
		return (true);
	return (false);
}

static	bool		newline_at_right(t_line_stat *stat)
{
	t_std	*std;
	t_line	*tmp;

	tmp = NULL;
	std = NULL;
	std = std_singleton(NULL);
	if (std && std->line && stat->cursor_index)
		tmp = move_list_to_cursor(&std->line_list, stat->cursor_index);
	if (tmp && tmp->c == NEWLINE_ANSI && tmp->next && tmp->next->c == '\n')
		return (true);
	return (false);
}

static inline void	motion_left(t_std *std)
{
	int		i;

	i = 0;
	ft_putstr_fd(MOVE_UP, 0);
	while (i < std->win.ws_col)
	{
		ft_putstr_fd(MOVE_RIGHT, 0);
		i++;
	}
}

void				move_left(t_line_stat *stat)
{
	t_std	*std;
	bool	is_nl;

	is_nl = false;
	std = std_singleton(NULL);
	if (stat->cursor_index != 0)
	{
		is_nl = newline_at_left(stat);
		if (stat->win_index == (std->win.ws_col * (stat->focus_line - 1)))
		{
			motion_left(std);
			stat->focus_line--;
		}
		else
			ft_putstr_fd(MOVE_LEFT, 0);
		stat->cursor_index--;
		stat->win_index = stat->prompt_size + stat->cursor_index;
	}
	if (is_nl)
		move_left(stat);
}

void				move_right(t_line_stat *stat)
{
	t_std	*std;
	bool	is_nl;

	is_nl = false;
	std = std_singleton(NULL);
	(stat->cursor_index) = (stat->cursor_index) + 1;
	(stat->win_index) = stat->prompt_size + (stat->cursor_index);
	is_nl = newline_at_right(stat);
	if ((stat->win_index) == (std->win.ws_col * ((stat->focus_line))))
	{
		ft_putstr_fd(MOVE_DOWN, 0);
		stat->focus_line++;
	}
	else
		ft_putstr_fd(MOVE_RIGHT, 0);
	if (is_nl)
		move_right(stat);
}

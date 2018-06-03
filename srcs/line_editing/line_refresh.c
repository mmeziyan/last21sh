/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 17:16:33 by juhallyn          #+#    #+#             */
/*   Updated: 2018/03/15 18:07:21 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static inline	void	move_up_del(void)
{
	size_t	i;

	i = 1;
	ft_putstr_fd(MOVE_UP, 0);
	while (i < std_singleton(NULL)->win.ws_col)
	{
		ft_putstr_fd(MOVE_RIGHT, 0);
		i++;
	}
	ft_putstr_fd(DELETE_BEHIND, 0);
}

void					refresh_line(t_line_stat *stat)
{
	t_std	*std;
	size_t	i;

	std = std_singleton(NULL);
	i = stat->cursor_index;
	move_begin(std->line_list, stat);
	ft_putstr_fd(CLEAR, 0);
	init_prompt_size(stat);
	print_prompt(0, stat->prompt_mode, stat->prompt_size);
	ft_putstr_fd(SAVE_POS, 0);
	if ((ioctl(0, TIOCGWINSZ, &(std)->win) == -1))
		ft_fatalexit("ioctl fail");
	if (std->line)
	{
		print_editing_list(std->line_list);
		move_begin(std->line_list, stat);
	}
	ft_putstr_fd(REST_POS, 0);
	while (stat->cursor_index < i)
		move_right(stat);
}

void					refresh_del(t_line *tmp, bool up, t_line_stat *stat)
{
	int		nb_char;
	size_t	j;

	nb_char = 0;
	j = stat->focus_line;
	if (!up)
		ft_putstr_fd(MOVE_LEFT, 0);
	else
		move_up_del();
	ft_putstr_fd(SAVE_POS, 0);
	ft_putstr_fd(DELETE_BEHIND, 0);
	if (tmp && tmp->next)
		print_editing_list(tmp->next);
	ft_putstr_fd(REST_POS, 0);
	ft_putstr_fd(VISUAL_CURSOR, 0);
}

void					refresh_add(t_line *tmp)
{
	log_fatal("refresh ADD");
	ft_putstr_fd(DELETE_BEHIND, 0);
	ft_putstr_fd(SAVE_POS, 0);
	if (tmp && tmp->next)
		print_editing_list(tmp->next);
	ft_putstr_fd(REST_POS, 0);
	ft_putstr_fd(MOVE_RIGHT, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_adding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:09:44 by juhallyn          #+#    #+#             */
/*   Updated: 2018/03/20 12:13:10 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_middle(t_line *prev, char key, t_line *next)
{
	t_line	*new;

	new = init_line(key);
	prev->next = new;
	new->next = next;
	new->prev = prev;
	next->prev = new;
}

void	add_char(t_line **edit_line, int key, t_line_stat *stat)
{
	t_line	*tmp;

	tmp = move_list_to_cursor(edit_line, stat->cursor_index);
	// log_success("1");
	if (!tmp || !tmp->next)
	{
		// log_success("2");
		add_end(&tmp, key);
			// log_success("c = %c", tmp->c);
		if (key == NEWLINE_ANSI)
			ft_putchar('^');
		else if (key == '\n')
			ft_putchar('J');
		else
			ft_putchar(key);
		// log_success("3");
	}
	else
	{
		if (tmp && tmp->next)
		{
			add_middle(tmp, key, tmp->next);
			refresh_add(tmp);
		}
	}
	// log_success("c = %c", tmp->next->c);
}

void	add_end(t_line **edit_line, int key)
{
	t_line	*tmp;

	tmp = NULL;
	if (!*edit_line)
	{
		*edit_line = init_line(key);
		return ;
	}
	tmp = *edit_line;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_line(key);
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
}

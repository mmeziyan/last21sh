/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:37:22 by juhallyn          #+#    #+#             */
/*   Updated: 2018/03/15 18:04:32 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	nl_backspace(t_line_stat *stat)
{
	t_std	*std;
	t_line	*tmp;

	tmp = NULL;
	std = std_singleton(NULL);
	tmp = move_list_to_cursor(&std->line_list, stat->cursor_index);
	if (tmp && tmp->c == '\n' && tmp->prev && tmp->prev->c == NEWLINE_ANSI)
		return (true);
	return (false);
}

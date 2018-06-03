/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:17:43 by juhallyn          #+#    #+#             */
/*   Updated: 2018/03/15 19:49:57 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	eof_key(t_line **edit_line, t_line_stat *stat)
{
	if ((*edit_line) && (*edit_line)->next && (*edit_line)->next->c)
		del_delete(stat, edit_line);
	else
	{
		init_term_canon(true);
		exit(0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:49:55 by juhallyn          #+#    #+#             */
/*   Updated: 2018/04/06 21:36:58 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line				*move_list_to_cursor(t_line **edit_line, \
					size_t cursor_index)
{
	t_line	*tmp;
	size_t	i;

	i = 0;
	tmp = *edit_line;
	while (i < (cursor_index) && (tmp))
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

size_t				list_len(t_line *edit_line)
{
	size_t	i;

	i = 0;
	if (!edit_line)
		return (0);
	if (edit_line->next)
		edit_line = edit_line->next;
	else
		return (0);
	while (edit_line)
	{
		edit_line = edit_line->next;
		i++;
	}
	return (i);
}

void				free_list(t_line **edit_line, bool std)
{
	t_line	*tmp;

	tmp = NULL;
	while (*edit_line)
	{
		tmp = (*edit_line)->next;
		free(*edit_line);
		*edit_line = tmp;
	}
	if (std)
		std_singleton(NULL)->line = NULL;
}

char				*remove_newline_ansi(char *command)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	if (!command)
		return (NULL);
	new = (char *)ft_memalloc(sizeof(char*) * ft_strlen(command));
	if (!new)
		ft_fatalexit("allocation fail of new in (remove_newline_ansi)");
	while (command[i])
	{
		if ((ft_strncmp(command + i, "\032J", 2) == 0))
		{
			new[j] = '\n';
			i++;
		}
		else
			new[j] = command[i];
		i++;
		j++;
	}
	ft_strdel(&command);
	return (new);
}

char				*malloc_str(t_line *edit_line)
{
	char	*command;
	size_t	len;

	len = list_len(edit_line);
	command = ft_strnew(len + 1);
	if (!command)
		ft_fatalexit("allocation error for command in list_to_str");
	return (command);
}

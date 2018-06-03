/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallx <hallx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:13:36 by hallx             #+#    #+#             */
/*   Updated: 2018/03/15 19:43:02 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				ft_fatalexit(char *error)
{
	if (error)
	{
		ft_putstr_fd("\x1b[31m", 2);
		ft_putendl_fd(error, 2);
		ft_putstr_fd("\x1b[0m", 2);
	}
	exit(-1);
}

void				ft_puterror(char *error)
{
	if (error)
	{
		ft_putstr_fd("\x1b[31m\nError : ", 2);
		ft_putendl_fd(error, 2);
		ft_putstr_fd("\x1b[0m", 2);
	}
}

/*
**				ft_atoi_mod
**	--	to convert string to one int value --
*/

int					ft_atoi_mod(char *str)
{
	int		*ptr;
	ptr = (int*)str;
	return (*ptr);
}

int					ft_ischar(int key)
{
	if ((key <= 126 && key >= 32) || key == 10)
		return (1);
	return (0);
}

/*
**			DEBUG
**	--	LOGGER function --
*/

int			print_editing_list_log(t_line *edit_line)
{
	int i = 0;

	if (!edit_line)
		return (0);
	while (edit_line)
	{
		if (edit_line->c != NEWLINE_ANSI)
			log_info("list->char : %c", edit_line->c);
		else
			log_info("list->char : NEWLINE_ANSI");
		edit_line = edit_line->next;
		i++;
	}
	return (i);
}


/*
**			DEBUG END
**	--	LOGGER function --
*/

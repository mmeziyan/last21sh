/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallx <hallx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 12:32:05 by hallx             #+#    #+#             */
/*   Updated: 2018/04/22 22:20:54 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_std	*std_singleton(t_std *std)
{
	static t_std	*std_stat;

	if (std)
		std_stat = std;
	return (std_stat);
}

void	init_std(t_std **std)
{
	// extern char 	**environ;

	
	if (!(*std = (t_std*)ft_memalloc(sizeof(t_std))))
		ft_fatalexit("can't allocate std in init_std");
	(*std)->history = init_history();

	// (*std)->command_line = NULL;
	// (*std)->line = NULL;
	// (*std)->command_line = NULL;
	(*std)->line = NULL;
	(*std)->line_list = NULL;
	(*std)->command_list = NULL;

	(*std)->ast = NULL;
	(*std)->myenv = NULL;
	(*std)->realfd[0] = dup(0);
	(*std)->realfd[1] = dup(1);
	(*std)->realfd[2] = dup(2);
	(*std)->stdin = !isatty(0) ? true : false;
	(*std)->ret = 0;
	(*std)->heredoc_line = NULL;
	// (*std)->env = env_cpy(environ);
	std_singleton(*std);
}

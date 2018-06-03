/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:25:59 by juhallyn          #+#    #+#             */
/*   Updated: 2018/04/23 02:14:09 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_quit(int ret, const char *error)
{
	// t_std	*std;

	// std = std_singleton(NULL);


	if (error)
		ft_putendl_fd(error, 2);
	logger_close();
	exit (ret);
}

static	void	stdin_mode(t_std *std)
{
	int		ret;

	ret = 0;
	if (!isatty(0))
	{
		ret = get_next_line(0, &std->line);
		if (ret == -1)
			ft_quit(-1, "read fail");
		if (ret == 0 && std->stdin == true)
			ft_quit(0, NULL);
	}
	else
	{
		
		// ft_putendl("sas");
		if ((ioctl(0, TIOCGWINSZ, &(*std).win) == -1))
			ft_fatalexit("ioctl fail");
		init_term_canon(false);
		line_editing(std->ret == 0 ? 0 : -1);
		ft_putendl("");
		
	}
}

int			main(void)
{
	t_std	*std;
	int		ret;
// LOGGER	---------------------------------------------------------------
	if (logger_init(D_TRACE, "out.log") != 0)
		printf("failed to open the logger\n");
// LOGGER	---------------------------------------------------------------
	std = NULL;
	ret = 0;
	init_std(&std);
	init_env();
	ft_signal();
	while (42)
	{
		stdin_mode(std);
		// if (!(std->lexer = lexing(std->line)))
		// {
		// 	std->ret = 0;
		// 	continue ;
		// }
		// if ((std->ast = process(std->lexer, NULL, 0)))
		// 	std->ret = std->ast->ret;
		// 	// graph(std->ast);
		
		// free_ast(&std->ast);
		// free_lexer(&std->lexer);
		// sleep(4);
	}
// LOGGER END -------------------------------------------------------------
	ft_quit(0, NULL);
	return (0);
}

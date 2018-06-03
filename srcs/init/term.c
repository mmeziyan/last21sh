/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:30:25 by juhallyn          #+#    #+#             */
/*   Updated: 2018/02/23 19:48:06 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void					termios_error(int succes)
{
	if (succes < 0)
		ft_fatalexit("Could not access the termcap data base.");
	if (succes == 0)
		ft_fatalexit("Terminal type is not defined");
}

static void						to_no_canonial(struct termios *term)
{
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_lflag |= ISIG;
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	// tcsetattr(0, TCSANOW, term);
}

// term_stat_cpy = my_memcpy(&t, st, sizeof(struct termios));


int init_term_canon(bool b_canon)
{
	static struct termios *canon = NULL;
	static struct termios *no_canon = NULL;
	char	*term_type;
	int 	ret;

	if (!canon)
	{
		canon = malloc(sizeof(struct termios));
		no_canon = malloc(sizeof(struct termios));
		// first_time = false;
		if (!(term_type = getenv("TERM")))
		{
			ft_putendl_fd("Could not access to $TERM var", 2);
			exit(-1);
		}
		if ((ret = tgetent(NULL, term_type)) < 1)
			termios_error(ret);
		if ((ret = tcgetattr(0, canon)))
			exit(-1);
		ft_memcpy(no_canon, canon, sizeof(struct termios));
		to_no_canonial(no_canon);
	}
	if (b_canon)
		tcsetattr(0, TCSANOW, canon);
	else
		tcsetattr(0, TCSANOW, no_canon);
	return (0);
}

// int							init_term_canon(bool canon)
// {
// 	char			*term_type;
// 	int				succes;
// 	struct termios	term;

// 	termios_sigleton(&term);
// 	if (!(term_type = getenv("TERM")))
// 	{
// 		ft_putendl_fd("Could not access to $TERM var", 2);
// 		exit(-1);
// 	}
// 	succes =	tgetent(NULL, term_type);
// 	if (termios_error(succes) == -1)
// 		exit(-1);
// 	succes = tcgetattr(0, &term);
// 	if (succes == -1)
// 		exit(-1);
// 	if (!canon)
// 		to_no_canonial(&term);
// 	else
// 		reset_term(&term);
// 	return (0);
// }



// void						reset_term(struct termios *term)
// {
// 	// struct termios term;
 
// // struct termios term;
 
// // if (tcgetattr(0, term) == -1)
// //    return ;
// term->c_lflag = (ICANON | ECHO);
// // term->c_cc = (ICANON | ECHO);
// ft_putstr_fd(tgetstr("ve", NULL), 0);
// if (tcsetattr(0, TCSANOW, term) == -1)
//    return ;
// // termios_sigleton(term);

// 	// if (tcgetattr(0, term) == -1)
// 	// 	return ;
// 	// term->c_lflag = (ICANON | ECHO);
// 	// if (tcsetattr(0, 0, term) == -1)
// 	// 	return ;
// 	// term->c_lflag &= (ICANON);
// 	// termios_sigleton(term);
// 	// term->c_lflag |= ISIG;
// 	// term->c_lflag |= ECHO;
// 	// ft_putstr_fd(tgetstr("ve", NULL), 0);
// 	// tcsetattr(0, TCSANOW, term);
// }

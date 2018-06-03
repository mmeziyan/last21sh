/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 12:07:19 by juhallyn          #+#    #+#             */
/*   Updated: 2018/04/08 16:21:32 by hpu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		ioctl(0, TIOCSTI, "\5\0");
	if (sig == SIGWINCH)
	{
		log_warn("SIZE CHANGED");
		ioctl(0, TIOCSTI, "\2\0");
	}
}

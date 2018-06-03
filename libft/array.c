/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 19:48:11 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/12/25 19:48:12 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	array_len(char **array)
{
	int	n;

	n = -1;
	while (array[++n])
		;
	return (n);
}

void	array_free(char ***array)
{
	int	n;

	n = -1;
	while ((*array)[++n])
	{
		free((*array)[n]);
		(*array)[n] = NULL;
	}
	free(*array);
	*array = NULL;
}

void	free_tab(char ***tab)
{
	int	n;

	n = -1;
	while ((*tab)[++n])
	{
		free((*tab)[n]);
		(*tab)[n] = NULL;
	}
	free(*tab);
	*tab = NULL;
}

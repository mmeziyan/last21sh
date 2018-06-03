/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_occurence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 19:48:11 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/12/25 19:48:12 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		last_occurence(char *str, char c)
{
	int		i;
	int		n;
	char	*ptr;

	n = -1;
	i = -1;
	ptr = NULL;
	while (str[++i])
		if (str[i] == c)
			n = i;
	return (n);
}

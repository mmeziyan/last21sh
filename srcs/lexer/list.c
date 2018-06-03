/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:54:04 by juhallyn          #+#    #+#             */
/*   Updated: 2018/04/10 18:37:19 by hpu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		lexer_add_end(t_lexer **lexer, char *data, t_token type)
{
	t_lexer		*tmp;

	if (!*lexer)
	{
		*lexer = create_lexer_node(data, type);
		return ;
	}
	tmp = *lexer;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = create_lexer_node(data, type);
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
}

t_lexer		*create_lexer_node(char *data, t_token type)
{
	t_lexer		*node;

	node = NULL;
	node = (t_lexer*)malloc(sizeof(*node));
	if (!node)
		ft_fatalexit("allocation fail for `node` in create_lexer_node");
	if (data)
		node->data = ft_strdup(data);
	else
		node->data = NULL;
	node->type = type;
	node->status = 0;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

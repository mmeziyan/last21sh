/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:40:24 by juhallyn          #+#    #+#             */
/*   Updated: 2018/04/11 20:21:13 by hpu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			print_lexer_idlist(t_lexer_id *lexer)
{
	t_token		token;

	log_fatal("---------    LEXER ID ENTRY   --------------------------------");
	token = INIT;
	log_fatal("INIT Value 		[%d]", token);
	token = SEMICOLON;
	log_fatal("SEMICOLON Value 		[%d]", token);
	token = AMPERSAND;
	log_fatal("AMPERSAND Value 		[%d]", token);
	token = REDIR_SUP;
	log_fatal("REDIR_SUP Value 		[%d]", token);
	token = REDIR_INF;
	log_fatal("REDIR_INF Value 		[%d]", token);
	token = D_REDIR_INF;
	log_fatal("D_REDIR_INF 		[%d]", token);
	token = D_REDIR_SUP;
	log_fatal("D_REDIR_SUP 		[%d]", token);
	token = AGGREGATOR;
	log_fatal("AGGREGATOR 		[%d]", token);
	token = IO_NUMBER;
	log_fatal("IO_NUMBER 			[%d]", token);
	token = NEWLINE;
	log_fatal("NEWLINE 			[%d]", token);
	token = DOLLAR;
	log_fatal("DOLLAR 			[%d]", token);
	token = QUOTE;
	log_fatal("QUOTE 			[%d]", token);
	token = DQUOTE;
	log_fatal("DQUOTE 			[%d]", token);
	token = PIPE;
	log_fatal("WORD Value 		[%d]", token);
	token = WORD;
	log_fatal("WORD Value 		[%d]", token);
	token = T_AND;
	log_fatal("T_AND Value 		[%d]", token);
	token = T_OR;
	log_fatal("T_OR Value 		[%d]", token);
	token = STD_SEPARATOR;
	log_fatal("STD_SEPARATOR Value	[%d]", token);
	while (lexer)
	{
		// log_info("data : [%c] | token : [%d]", lexer->data, lexer->type);
		lexer = lexer->next;
	}
}

t_lexer_id		*create_lexer_id_node(char data, t_token type)
{
	t_lexer_id		*node;

	node = NULL;
	node = (t_lexer_id*)malloc(sizeof(*node));
	if (!node)
		ft_fatalexit("allocation fail for `node` in create_lexer_id_node");
	node->data = data;
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void		lexer_id_add_end(t_lexer_id **lexer, char data, t_token type)
{
	t_lexer_id		*tmp;

	tmp = NULL;
	if (!*lexer)
	{
		*lexer = create_lexer_id_node(data, type);
		return ;
	}
	tmp = *lexer;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = create_lexer_id_node(data, type);
	tmp->next->prev = tmp;
	// tmp->next->next = NULL;
}

t_lexer_id		*lexer_id_init(void)
{
	t_lexer_id	*node;

	node = NULL;
	node = (t_lexer_id*)malloc(sizeof(*node));
	if (!node)
		ft_fatalexit("allocation fail node in lexer_init");
	node->data = '\0';
	node->type = INIT;
	return (node);
}

void			free_lexer_id(t_lexer_id **lexer_id)
{
	t_lexer_id	*tmp;

	tmp = NULL;
	while (*lexer_id)
	{
		tmp = (*lexer_id)->next;
		free(*lexer_id);
		(*lexer_id) = tmp;
	}
}

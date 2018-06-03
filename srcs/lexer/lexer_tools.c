/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 19:26:32 by juhallyn          #+#    #+#             */
/*   Updated: 2018/04/22 17:20:13 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool			is_escape(char *str, size_t i)
{
	size_t	j;
	bool	status;

	status = false;
	if (i == 0)
		i = 1;
	if (str && str[i])
	{
		j = i - 1;
		while (str[j])
		{
			if (str[j] == '\\')
				status = !status;
			else
				return (status);
			j--;
		}
	}
	return (status);
}

static void		check_io_number(t_lexer *lexer)
{
	size_t		i;

	i = 0;
	if (!lexer)
		return ;
	while (lexer->next)
		lexer = lexer->next;
	if (lexer && lexer->data)
	{
		while (lexer->data[i])
		{
			if (ft_isdigit(lexer->data[i]) != 1)
				return ;
			i++;
		}
		lexer->type = IO_NUMBER;
	}
}

void			add_token(t_lexer_id *id_ptr, t_lexer **lexer, size_t len)
{
	size_t	i;
	char	*data;
	t_token	type;

	if (!id_ptr)
		return ;
	i = 0;
	type = id_ptr->type;
	data = ft_strnew(len);
	if (!data)
		ft_fatalexit("allocation failed to `data` in add_token()");
	if (type == REDIR_SUP || type == D_REDIR_SUP || type == REDIR_INF)
		check_io_number(*lexer);
	while (len && id_ptr)
	{
		data[len - 1] = id_ptr->data;
		id_ptr = id_ptr->prev;
		len--;
		if (!len)
			lexer_add_end(lexer, data, type);
	}
	if (data)
		ft_strdel(&data);
}

void			print_lexer_list(t_lexer *lexer)
{
	log_debug("------------------ LEXER ----------------------------");
	if (!lexer)
	{
		log_debug("! LEXER IS NULL");
		return ;
	}
	while (lexer)
	{
		if (lexer->data)
			log_info("data : [%s], type : [%d]", lexer->data, lexer->type);
		lexer = lexer->next;
	}
}

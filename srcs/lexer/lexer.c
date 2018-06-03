/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:15:01 by juhallyn          #+#    #+#             */
/*   Updated: 2018/04/11 17:32:19 by hpu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			free_lexer(t_lexer **lexer)
{
	t_lexer		*tmp;

	tmp = NULL;
	while (*lexer)
	{
		tmp = (*lexer)->next;
		ft_strdel(&(*lexer)->data);
		free(*lexer);
		(*lexer) = tmp;
	}
}

static	void	join_redir(t_lexer_id *id, size_t *len, \
				t_token *act_type)
{
	*len = *len + 1;
	if (*act_type == REDIR_SUP)
		id->type = D_REDIR_SUP;
	if (*act_type == AMPERSAND)
		id->type = T_AND;
	if (*act_type == PIPE)
		id->type = T_OR;
	if (*act_type == REDIR_INF)
		id->type = D_REDIR_INF;
}

void			join_lexical_operator(t_lexer_id *id, t_lexer **lexer, \
				size_t *len, t_token *act_type)
{
	if (*len == 1 && id->type == *act_type && (*act_type == REDIR_SUP
	|| *act_type == REDIR_INF || *act_type == AMPERSAND 
	|| *act_type == AMPERSAND || *act_type == PIPE))
		join_redir(id, len, act_type);
	else
	{
		add_token(id->prev, lexer, *len);
		*act_type = id->type;
		*len = 1;
	}
}

void 			tokenizer(t_lexer_id *lexer_id, t_lexer **lexer)
{
	t_lexer_id	*id_tmp;
	t_token		act_type;
	size_t		len;

	if (!lexer_id)
		return ;
	len = 0;
	id_tmp = NULL;
	act_type = lexer_id->type;
	while (lexer_id)
	{
		if ((lexer_id->type == WORD || lexer_id->type == DOLLAR) \
		&& (act_type == WORD || act_type == DOLLAR))
			len++;
		else
			join_lexical_operator(lexer_id, lexer, &len, &act_type);
		id_tmp = lexer_id;
		lexer_id = lexer_id->next;
	}
	if (len)
		add_token(id_tmp, lexer, len);
}

// static int	d_quote(const char *s, int n, bool *quote, bool *dquote)
// {
// 	int		i;

// 	i = 0;

// 	if (!s[i + n])
// 		return (3);
// 	if (*quote == true && s[i + n] != '\'')
// 		return (0);
// 	if ((*quote == true && s[i + n] == '\'') 
// 	|| (*dquote == false && s[i + n] == '\'' && !is_escape((char *)s, n + i)))
// 	{
// 		*quote = !*quote;
// 		return (1);
// 	}
// 	if (!is_escape((char *)s, n + i) && s[i + n] == '"')
// 	{
// 		*dquote = !*dquote;
// 		return (1);
// 	}
// 	if (*dquote && s[i + n] == ' ')
// 		return (0);
// 	if (is_escape((char *)s, n + i))
// 		return (2);
// 	if (s[i + n] == ' ')
// 		return (3);
// 	return (0);

// 	// if (!is_escape((char *)s, n + i) && s[i + n] == '\'' && !*dquote)
// 	// {
// 	// 	*quote = !*quote;
// 	// 	return (1);
// 	// }
// 	// else if (*quote == true && s[i + n] == '\'')
// 	// {

// 	// }

// 	// // if (!is_escape((char *)s, n + i) && s[i + n] == '"')
// 	// // {
// 	// // 	*dquote = !*dquote;
// 	// // 	return (1);
// 	// // }



// 	// if (*dquote == true && !is_escape((char *)s, n + i))
// 	// {
// 	// 	if ()

// 	// 	return (0);
// 	// // if (*dquote == true && s[i + n] != '\'')
// 	// 	// return (0);
// 	// // if (s[i + n] )
// 	// // if (*dquote == true)
// 	// // {

// 	// // }
// 	// if (!is_escape((char *)s, n + i))
// 	// {
// 	// 	if (s[i + n] == '"' && !*quote)
// 	// 	{
// 	// 		*dquote = !*dquote;
// 	// 		return (1);
// 	// 	}
// 	// 	else if (s[i + n] == '\'' && !*dquote)
// 	// 	{
// 	// 		*quote = !*quote;
// 	// 		return (1);
// 	// 	}
// 	// 	else if (s[i + n] == ' ' || s[i + n] == '\t')
// 	// 		return (3);
// 	// 	// else
// 	// 	// 	return (0);
// 	// }
// 	// else
// 	// {

// 	// }
// 	// // if (*quote == true || (s[i + n] == ' ' && *dquote == true))
// 	// // 	return (0);
// 	// // if ((s[i + n] == '"' && !*quote) || (s[i + n] == '\'' && !*dquote)
// 	// // || s[i + n] == '\\' || s[i + n] == ' ')
// 	// // 	return (2);
// 	// return (0);
// }

// static int	lexer_real_word_len(char *command)
// {
// 	bool	quote = false;
// 	bool	dquote = false;
// 	int		i;
// 	int		j;
// 	int		ret;

// 	ret = 0;
// 	i = 0;
// 	j = 0;
// 	while (command[i + j])
// 	{
// 		if ((ret = d_quote(command, i + j, &quote, &dquote)) == 3)
// 			return (i);
// 		my_printf("ret = %i, char = [%c]\n", 0, ret, command[i + j]);
// 		// {
// 		// 	j++;
// 		// 	continue ;
// 		// }
// 		if (ret == 0)
// 			i++;
// 		else
// 			j++;
// 	}
// 	// while (command[i + j])
// 	// {
// 	// 	if ((ret = d_quote(command, i + j, &quote, &dquote)) > 0)
// 	// 	{
// 	// 		j++;
// 	// 		continue ;
// 	// 	}
// 	// 	if (ret == 3)
// 	// 		return (i);
// 	// 	i++;
// 	// }
// 	return (i);
// }

// char	*lexer_word_create(char *command, bool *quote, bool *dquote)
// {
// 	int	i;
// 	int	j;
// 	int ret;
// 	char *new;
	
// 	i = lexer_real_word_len(command);
// 	if (!(new = malloc(sizeof(char) * (i + 1))))
// 		exit (-1);
// 	j = 0;
// 	i = 0;
// 	while (command[i + j])
// 	{
// 		if ((ret = d_quote(command, i + j, quote, dquote)) == 2)
// 		{
// 			new[i - 1] = command[i + j++];
// 			continue ;
// 		}
// 		if (ret == 3)
// 		{
// 			new[i] = '\0';
// 			return (new);
// 		}
// 		if (ret == 1)
// 			j++;
// 		new[i] = command[i + j];
// 		i++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

// static char		*sss(char *command)
// {
// 	char	*new;
// 	// int		i;
// 	int		j;
// 	bool	quote = false;
// 	bool	dquote = false;

// 	// i = 0;
// 	// j = lexer_word_len(command);
// 	new = lexer_word_create(command, &quote, &dquote);

// 	ft_putendl(new);
// 	// ft_putnbr(j);ft_putendl("");
// 		// while (s[i] && (s[i] == ' ' || s[i] == '\t'))
// 			// i++;
// 		// word = d_quote(s, i);

// 			// res[j++] = ft_strsub(s, i, word);
// 		// i += word;
	
// 	// res[j] = NULL;
// 	return (new);
// }


// char			*remove_quote(char *command)
// {
// 	char	*new;
// 	int		n;
// 	int		i;
// 	bool	quote;
// 	bool	quote;

// 	n = 0;
// 	i = -1;
// 	quote = false;	
// 	while (command[++i])
// 	{


// 		n++;
// 		// if ()
// 	}
// 	// if (command[i] == '\\' && command[i + 1] == '\\')
// 	// 	i++;
// 	// if (command[i] == '$')
// }

t_lexer			*lexing(char *command)
{
	t_lexer_id		*lexer_id;
	t_lexer			*lexer;

	lexer = NULL;
	if (!command)
		return (NULL);
	command = remove_newline_ansi(command);
	// d_quote(command, 0);
	// command = sss(command);
	// command = remove_quote(command);
	lexer_id = analyse(command);
	print_lexer_idlist(lexer_id);
	tokenizer(lexer_id, &lexer);
	free_lexer_id(&lexer_id);
	print_lexer_list(lexer);
	return (lexer);
}

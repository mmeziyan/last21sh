/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpu <hpu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:40:48 by hpu               #+#    #+#             */
/*   Updated: 2018/04/11 18:40:50 by hpu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static int	d_quote(const char *s, int n)
{
	bool	quote;
	bool	dquote;
	int		i;

	i = 0;
	quote = false;
	dquote = false;
	while (s[i + n] && ((s[i + n] != ' ' && s[i + n] != '\t') \
	|| quote == true || dquote == true))
	{
		if (!is_escape((char *)s, n + i))
		{
			dquote = (s[i + n] == '"') ? !dquote : dquote;
			quote = (s[i + n] == '\'') ? !quote : quote;
		}
		i++;
	}
	return (i);
}

static int	count_word(char const *s)
{
	int	i;
	int	word;

	if (s == NULL)
		return (0);
	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		i += d_quote(s, i);
		if (i > 0 && (s[i - 1] != ' ' && s[i - 1] != '\t'))
			word++;
	}
	return (word);
}

char		**lexer_split(char *s)
{
	char	**res;
	int		i;
	int		j;
	int		word;

	word = count_word(s);
	if (!s || !(res = ft_memalloc(sizeof(char **) * (word + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		word = d_quote(s, i);
		if (word > 0)
			res[j++] = ft_strsub(s, i, word);
		i += word;
	}
	res[j] = NULL;
	return (res);
}


































// static int	d_quote(const char *s, int n, bool *quote, bool *dquote)
// {
// 	int		i;

// 	i = 0;
// 	if (!s[i + n])
// 		return (4);
// 	if (*quote == true && s[i + n] != '\'')
// 		return (0);
// 	if ((*quote == true && s[i + n] == '\'') 
// 	|| (*dquote == false && s[i + n] == '\'' && !is_escape((char *)s, n + i)))
// 	{		
// 		*quote = !*quote;
// 		// ft_putnbr(*quote);
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
// }
// // // static int	d_quote(const char *s, int n, bool *quote, bool *dquote)
// // // {
// // // 	int		i;

// // // 	i = 0;
// // // 	if (!is_escape((char *)s, n + i))
// // // 	{
// // // 		if (s[i + n] == '"' && !*quote)
// // // 		{
// // // 			*dquote = !*dquote;
// // // 			return (1);
// // // 		}
// // // 		else if (s[i + n] == '\'' && !*dquote)
// // // 		{
// // // 			*quote = !*quote;
// // // 			return (1);
// // // 		}
// // // 		else if (s[i + n] == ' ' && !*dquote)
// // // 			return (3);
// // // 		else
// // // 			return (0);
// // // 	}
// // // 	if (*quote == true || (s[i + n] == ' ' && *dquote == true))
// // // 		return (0);
// // // 	if ((s[i + n] == '"' && !*quote) || (s[i + n] == '\'' && !*dquote)
// // // 	|| s[i + n] == '\\' || s[i + n] == ' ')
// // // 		return (2);
// // // 	return (0);
// // // }

// // // static int	d_quote(const char *s, int n)
// // // {
// // // 	bool	quote;
// // // 	bool	dquote;
// // // 	int		i;

// // // 	i = 0;
// // // 	quote = false;
// // // 	dquote = false;
// // // 	while (s[i + n] && ((s[i + n] != ' ' && s[i + n] != '\t') \
// // // 	|| quote == true || dquote == true))
// // // 	{
// // // 		if (!is_escape((char *)s, n + i))
// // // 		{
// // // 			dquote = (s[i + n] == '"') ? !dquote : dquote;
// // // 			quote = (s[i + n] == '\'') ? !quote : quote;
// // // 		}
// // // 		i++;
// // // 	}
// // // 	return (i);
// // // }

// // // static int	count_word(char const *s)
// // // {
// // // 	int	i;
// // // 	int	word;

// // // 	if (s == NULL)
// // // 		return (0);
// // // 	word = 0;
// // // 	i = 0;
// // // 	while (s[i])
// // // 	{
// // // 		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
// // // 			i++;
// // // 		i += d_quote(s, i);
// // // 		if (i > 0 && (s[i - 1] != ' ' && s[i - 1] != '\t'))
// // // 			word++;
// // // 	}
// // // 	return (word);
// // // }
// // static int	nb_word(char *command)
// // {
// // 	bool	quote = false;
// // 	bool	dquote = false;
// // 	int		i;
// // 	int		j;
// // 	int		ret;

// // 	ret = 0;
// // 	i = 0;
// // 	j = 0;
// // 	while (command[i + j])
// // 	{
// // 		// ft_putchar(command[i + j]);
// // 		if ((ret = d_quote(command, i + j, &quote, &dquote)) < 3)
// // 			i++;
// // 		else if (ret == 3)
// // 		{
// // 			ft_putchar(command[i + j - 1]);	
// // 			j++;
// // 			while((ret = d_quote(command, i + j, &quote, &dquote)) == 3)
// // 				i++;
// // 			// continue ;
// // 		}
// // 		// else
// // 			// return (j);
// // 		// else
// // 		// 	i++;
// // 		// while((ret = d_quote(command, i + j, &quote, &dquote)) == 3)
// // 		// {
// // 		// 	j++;
// // 		// 	continue ;
// // 		// }
// // 		// if (ret == 3)
// // 			// j++;
		
// // 	}
// // 	// ft_putnbr(j);
// // 	return (j);
// // }

// // static int	lexer_word_len(char *command)
// // {
// // 	bool	quote = false;
// // 	bool	dquote = false;
// // 	int		i;
// // 	int		j;
// // 	int		ret;

// // 	ret = 0;
// // 	i = 0;
// // 	j = 0;
// // 	while(d_quote(command, i + j, &quote, &dquote) == 3)
// // 		j++;
// // 	while (command[i + j])
// // 	{
// // 		if ((ret = d_quote(command, i + j, &quote, &dquote)) == 3)
// // 			return (i);
// // 		// my_printf("ret = %i, char = [%c]\n", 0, ret, command[i + j]);
// // 		// {
// // 		// 	j++;
// // 		// 	continue ;
// // 		// }
// // 		// if (ret == 0)
// // 			// j++;
// // 		// else
// // 		i++;
// // 	}
// // 	return (i);
// // }

// char		**lexer_split(char *command)
// {
// 	char	**new;
// 	int		i[4];
// 	bool	quote;
// 	bool	dquote;
// 	// int		i;
// 	// int		j;
// 	// int		word;

// 	i[2] = nb_word(command);
// 	i[2]++;
// 	ft_putnbr(i[2]);ft_putendl("  |");
	
// 	if (!command || !(new = ft_memalloc(sizeof(char **) * (i[2] + 1))))
// 		return (NULL);
// 	quote = false;
// 	dquote = false;
// 	i[0] = 0;
// 	i[1] = 0;
// 	while (i[2]--)
// 	{
// 		// i[3] = i[0];
// 		// i[0] = lexer_word_len(&command[i[0]]);
// 		// i[3] 
// 		// ft_putendl("");ft_putnbr(i[0]); ft_putendl("");
// 		while (d_quote(command, i[0], &quote, &dquote) != 3)
// 		{
			
// 		}
// // ft_putnbr(i[0]);ft_putendl("");
// 		// i[0] += i[3] + 1;
// 		// ft_putnbr(i[0]); 
// 		// ft_putendl(&command[i[3]]);
		
// 		new[i[1]] = lexer_word_create(&command[i[3]], &quote, &dquote);
// 		// ft_putendl(new[i[1]]);
// 		// ft_putnbr(ft_strlen(new[i[1]]));my_printf("new[%i]: %s\n", 2, i[1], new[i[1]] ); sleep(1);
// 		if (new[i[1]])
// 			i[1]++;
// 		// i[0] += i[3];
		
// 		// i[0] += ft_strlen(new[i[1]++]) + 2;
// 		// while (s[i] && (s[i] == ' ' || s[i] == '\t'))
// 			// i++;
// 		// word = d_quote(s, i);
// 		// if (word > 0)
// 			// res[j++] = ft_strsub(s, i, word);
// 		// i += word;
// 	}

// 	new[i[1]] = NULL;
// 	return (new);
// }

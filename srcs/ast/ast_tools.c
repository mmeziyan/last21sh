/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hp <hp@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:41:23 by hp                #+#    #+#             */
/*   Updated: 2018/04/23 15:44:15 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


t_ast *new_node(t_lexer *node, t_ast *parent)
{
	t_ast *new;

	// while (node && node->prev && node->prev->status != 1)
		// node = node->prev;
	if (!(new = malloc(sizeof(t_ast))))
		ft_fatalexit("allocotion fail : malloc new_node");
	new->type = node->type;
	new->parent = parent;
	new->lexer_node = node;
	new->ret = 0;
	new->data = NULL;
	new->argv = NULL;
	new->right = NULL;
	new->left = NULL;
	return (new);
}

void 		free_ast(t_ast **ast)
{
	int i;

	i = -1;
    if (!(*ast))
        return ;
	if ((*ast)->argv)
	{
		while ((*ast)->argv[++i])
			ft_strdel(&(*ast)->argv[i]);
		free((*ast)->argv);
	}
    if ((*ast)->data)
        free(&(*ast)->data);
    if ((*ast)->right)
        free_ast(&(*ast)->right);
    if ((*ast)->left)
        free_ast(&(*ast)->left);
    free(*ast);
    *ast = NULL;
}

int 		is_operator(t_lexer *lex)
{
    if (lex && lex->type && (lex->type > 0 && lex->type <= 5))
        return (0);
    return (1);
}

char *lexer_to_str(t_lexer *token)
{
	char *str;
	t_lexer *tmp;
	char *tmpstr;

	if (!is_operator(token))
		return (ft_strdup(token->data));
	tmp = token;
	str = ft_strnew(0);
	while (tmp && tmp->status != 1)
	{
		tmpstr = str;
		str = ft_strjoin(str, tmp->data);
		free(tmpstr);
		tmp = tmp->next;
	}
	return (str);
}
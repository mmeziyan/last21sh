/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpu <hpu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 20:12:55 by hpu               #+#    #+#             */
/*   Updated: 2018/04/11 23:51:22 by hpu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast		*new_root(t_lexer *lexer_node)
{
	t_ast	root;

	root = NULL;
	root = (t_ast*)malloc(sizeof(*root));
	if (!root)
		ft_fatalexit("allocation fail for `root` in new_head");
	root->type = 42;
	root->lexer_node = NULL;
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
}

// void		add_right(t_ast **ast, t_lexer *lexer_node)
// {
	
// }

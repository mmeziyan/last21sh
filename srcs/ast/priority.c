#include "shell.h"

t_lexer		*move_to_end(t_lexer *separator, int info)
{
    t_lexer *lexer_tmp;
    t_std   *std;

    std = std_singleton(NULL);
    if ((info == 1 || info == 3) && separator)
        return (separator->prev);
    if ((info == 2 || info == 4) && separator)
        lexer_tmp = separator->next;
    else
        lexer_tmp = std->lexer;
    while (lexer_tmp->next && !lexer_tmp->next->status)
        lexer_tmp = lexer_tmp->next;
    return (lexer_tmp);
}

t_lexer *priority(t_ast *parent, int info)
{
    t_lexer *tmp;
	t_lexer *end;
    int n;

	end = move_to_end((parent ? parent->lexer_node : NULL), info);
    n = 0;
    while (n <= 3)
    {
        tmp = end;
        while (tmp && !tmp->status)
        {
            if (n == 0 && tmp->type == SEMICOLON)
                return (tmp);
            if (n == 1 && (tmp->type == T_AND || tmp->type == T_OR))
                return (tmp);
            if (n == 2 && tmp->type == PIPE)
                return (tmp);
            if (n == 3 && (tmp->type >= REDIR_SUP && tmp->type <= D_REDIR_SUP))
                return (tmp);
            tmp = tmp->prev;
        }
        n++;
    }
    return (end);
}

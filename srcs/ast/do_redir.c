
#include "shell.h"

void	do_redir(void)
{
	t_redir		*head;

	head = grep_head(NULL, false);
	while (head)
	{
		head->fd_out_cpy = dup(head->fd_out);
		head = head->next;
	}
	head = grep_head(NULL, false);
	while(head)
	{
		if (head->fd_out == -2)
		{
			head = head->next;
			continue ;
		}
		if (head && head->fd_out == -1)
		{
			my_printf("21sh : %i: Bad file descriptor\n", 2, head->fd_out);
			return ;
		}	
		dup2(head->fd_in, head->fd_out);
		if (head->fd_in > 2)
			close (head->fd_in);
		head = head->next;
	}
}
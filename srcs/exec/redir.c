
#include "shell.h"
#include <errno.h>

int		ft_creat_file(char *file, t_token type, int info)
{
	int fd_out;
	char c;

	c = 1;
	if (type == REDIR_SUP)
	{
		fd_out = open(file,\
		O_WRONLY | O_TRUNC | O_CREAT,\
		S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH);
	}
	if (type == D_REDIR_SUP)
	{
		fd_out = open(file, O_RDWR);
		if (fd_out == -1)
			fd_out = open(file, O_RDWR | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH);
		if (info == 1)
			while(fd_out > 0 && read(fd_out, &c, 1) > 0)
				;
	}
	if (type == REDIR_INF)
		fd_out = open(file, O_RDONLY);
	if (fd_out == -1)
		my_printf("21sh: can't create %s: permission denied\n", 2, file);
	return (fd_out);
}

// static	void	read_and_right(t_ast *left, int fd_out)
// {
// 	char c;
// 	int ret_read;
// 	int fd_in;

// 	// fd_in = ft_creat_file(left, 0);
// 	fd_in = open(left->new_data ? left->new_data : left->argv[0] , O_RDONLY);
// 	log_debug("fdout : %i , ftin : %i", fd_out, fd_in);	
// 	ret_read = read(fd_in, &c, 1);
// 	ft_putnbr(ret_read);
// 	while (ret_read > 0)
// 	{
// 		write(fd_out, &c, 1);
// 		ret_read = read(fd_in, &c, 1);
// 	}
// 	close(fd_out);
// 	close(fd_in);
// }

// static void	ft_forked(t_ast *parent, t_ast *left, int fd_out)
// {
// 	int	ret;

// 	ret = 0;

// 	if (!left->new_data)
// 	{
// 		// log_debug("left->new_data %s    right : %s", parent->left->new_data, parent->right->new_data);	
// 		// parent->new_data = ft_strdup(parent->right->argv[0]);
// 		log_debug("parent->right->argv[0]-> %s", parent->right->argv[0]);	
// 		ret = dup2(fd_out, 1);
// 		if (ret == -1)
// 			perror("dup2");
// 		close(fd_out);
// 		exec(left);
// 		parent->ret = -1;
// 		exit(-1);
// 	}
// 	else
// 	{
// 		// log_debug("else");	
// 		// parent->new_data = ft_strdup(parent->right->lexer_node->data);
// 		read_and_right(left, fd_out);
// 		if (parent->type == REDIR_SUP)
// 		close(ft_creat_file(left, 0));
// 	}
// 	exit(0);
// }

// void		do_redirection(t_ast *parent, t_ast *left, t_ast *right)
// {
// 	pid_t	son;
// 	t_std	*std;
// 	int		status;
// 	int		fd_out;

// 	std = std_singleton(NULL);
// 	if ((fd_out = ft_creat_file(right, 0)) == -1)
// 		return ;
// 	// log_debug("left->new_data %s    right : %s", parent->left->new_data, parent->right->new_data);
// 	parent->new_data = ft_strdup(right->new_data ? right->new_data : right->argv[0]);
// 	if ((son = fork()) == -1)
// 		ft_fatalexit("fork error");
// 	if (son == 0)
// 		ft_forked(parent, left, fd_out);
// 	if (son > 0)
// 	{
// 		// parent->new_data = ft_strdup(left->new_data ? left->new_data : left->argv[0]);
// 		waitpid(son, &status, WUNTRACED | WCONTINUED);
// 		// if (WIFEXITED(status))
//         	// parent->ret = WEXITSTATUS(status);
// 	}

// }


#include "shell.h"

int		right(const char *path)
{
	struct stat	sta;

	lstat(path, &sta);
	if (sta.st_mode & S_IXUSR)
		return (1);
	return (0);
}


int		execute(t_std *std, t_ast *ast)
{
	int		n;
	char	*prog;

	prog = NULL;
	n = -1;
	if ((ft_strncmp(ast->argv[0], "./", 2) == 0 || ast->argv[0][0] == '/') && \
		access(ast->argv[0], X_OK) == 0)
		execve(ast->argv[0], ast->argv, std->myenv);
	while (std->path && std->path[++n])
	{
		prog = ft_strjoins(3, std->path[n], "/", ast->argv[0]);
		if (access(prog, X_OK) == 0)
		{
			execve((const char *)prog, ast->argv, std->myenv);
		}
		if (access(prog, F_OK) == 0 && !right(prog))
		{
			my_printf("21sh: permission denied: %s\n", 2, ast->argv[0]);
			return(-1);
		}
		ft_strdel(&prog);
	}
	if (access(ast->argv[0], F_OK) == 0 && !right(ast->argv[0]))
		my_printf("21sh: permission denied: %s\n", 2, ast->argv[0]);
	else
		my_printf("21sh: command not found: %s\n", 2, ast->argv[0]);
	return(-1);
}

char	**cmd_create(t_lexer *lexer_node)
{
	char	**cmd;
	t_lexer *lexer_tmp;
	int		n;

	n = 0;
	lexer_tmp = lexer_node;
	while(lexer_tmp && lexer_tmp->status != 1)
	{
		if (lexer_tmp->type == WORD && lexer_tmp->status != 2)
			n++;
		lexer_tmp = lexer_tmp->next;
	}
	cmd = ft_memalloc(sizeof(char *) * (n + 1));
	cmd[n] = NULL;
	n = -1;
	while(lexer_node && (lexer_node->status != 1))
	{
		if (lexer_node->type == WORD && lexer_node->status != 2)
			cmd[++n] = ft_strdup(lexer_node->data);
		lexer_node = lexer_node->next;
	}
	// n = 0;
	// while(cmd[n])
		// ft_putendl(cmd[n++]);
	return (cmd);
}

int		exec(t_ast *ast)
{
	t_std	*std;
	pid_t	son;
	int		status;

	// init_term_canon(true);
	init_term_canon(true);
	std = std_singleton(NULL);
	env_list_to_tab();
	recupath();
	if (builtins(ast) == 0)
		return (0);
	if ((son = fork()) == -1)
		ft_fatalexit("fork error");
	if (son == 0)
	{
		
		execute(std, ast);
		exit(-1);
	}
	else
	{
		init_term_canon(false);
		waitpid(son, &status, WUNTRACED | WCONTINUED);
		if (WIFEXITED(status))
     	   	return (ast->ret = WEXITSTATUS(status));
		// init_term_canon(false);
	}
	return (-1);
}

// int		execute_cmd(char *command)
// {
// 	log_warn("execution...");
// 	command = remove_newline_ansi(command);
// 	log_warn(" -> \n[%s]", command);
// 	if (command && ft_strcmp("exit", command) == 0)
// 	{
// 		// init_term_canon(true);
// 		exit(0);
// 	}
// 	ft_putstr_fd("\n", 0);
// 	// init_term_canon(true);
// 	system(command);
// 	ft_strdel(&command);
// 	// init_term_canon(false);
// 	return (0);
// }

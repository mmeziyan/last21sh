
# include "shell.h"

int				buil_env(t_ast *ast)
{
	if (ft_strcmp(ast->argv[0], "env\0") != 0)
		return (0);
	put_env();
	return (1);
}

int		buil_unset(t_ast *ast)
{
	int	n;

	n = 0;
	if (ft_strcmp(ast->argv[0], "unsetenv\0") != 0)
		return (0);
	while (ast->argv[++n])
	{
		if (ft_strchr(ast->argv[n], '='))
		{
			my_printf("unsetenv: %s: not a valid identifier\n", 2, ast->argv[n]);
			continue ;
		}
		env_del(ast->argv[n]);
	}
	return (1);
}

int		buil_setenv(t_ast *ast)
{
	if (ft_strcmp(ast->argv[0], "setenv\0") != 0)
		return (0);
	if (!ast->argv[1])
		put_env();
	if (ast->argv[1] && ast->argv[2] && ast->argv[3])
		my_printf("21sh : setenv: too many arguments\n", 2);
	if (ast->argv[1] && ast->argv[2] && !ast->argv[3])
	{
		if (ast->argv[1][0] == '_' && ast->argv[1][1] == '\0')
			return (1);
		if (ft_strchr(ast->argv[1], '=') || !ft_isalpha(ast->argv[1][0]))
		{
			my_printf("21sh: '%s': not a valid identifier\n", 2, ast->argv[1]);
			return (1);
		}
		add_env(ast->argv[1], ast->argv[2]);
	}
	return (1);
}


# include "shell.h"

void	init_env(void)
{
	extern char 	**environ;
	int				n;
	char			*ptr;
	t_env			*new;

	n = -1;
	while (environ[++n])
	{
		if (!(ptr = ft_strchr(environ[n], '=')))
			exit(-1);
		if (!(new = malloc(sizeof(t_env))))
			exit(-1);
		new->next = NULL;
		new->name = ft_strndup(environ[n], ptr - &environ[n][0]);
        if (ft_strcmp(new->name, "SHLVL") == 0 && (ptr + 1))
            new->value = ft_itoa(ft_atoi(ptr + 1));
        else
            new->value = *(ptr + 1) ? ft_strdup(ptr + 1) : NULL;
		add_right(new);
	}
    if (!env_search("SHLVL"))
        add_env("SHLVL", "1");
}
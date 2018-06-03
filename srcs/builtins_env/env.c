
#include "shell.h"

void	env_list_destroy(void)
{
	t_env *head;
	t_env *prev;

	head = grep_env_head(NULL, false);
	while (head)
	{
		prev = head;
		head = head->next;
		if (prev->name)
			ft_strdel(&prev->name);
		if (prev->value)
			ft_strdel(&prev->value);
		free(prev);
	}
	
	// grep_env_head(NULL, true);
}

void	env_del(char *name)
{
	t_env	*prev;
	t_env	*head;

	head = grep_env_head(NULL, false);
	// if (ft_strcmp(name, "PATH") == 0)
		// array_free(&std_singleton(NULL)->path);
	// if (std_singleton(NULL)->myenv)
		// env_list_destroy();
	prev = NULL;
	while (head)
	{
		if (ft_strcmp(head->name, name) == 0)
		{
			if (!prev)
				grep_env_head(head->next, true);
			else
				prev->next = head->next;
			ft_strdel(&head->name);
			if (head->value)
				ft_strdel(&head->value);
			free(head);
			std_singleton(NULL)->nb_env--;
		}
		prev = head;
		head = head->next;
	}
}

void	recupath(void)
{
	t_env	*tmp;
	t_std	*std;

	std = std_singleton(NULL);
	// char 	**path;

	if (std->path)
		array_free(&(std_singleton(NULL)->path));
	// path = NULL;
	// if (!std_singleton(NULL)->path)
		if ((tmp = env_search("PATH")) && tmp->value)
		{
			if (!(std->path = (ft_strsplit(tmp->value, ':'))))
				ft_fatalexit("split error");
		}
}

void	add_env(char *name, char *value)
{
	t_env	*new;
	t_std	*std;

	std = std_singleton(NULL);
	std->nb_env++;
	// if (ft_strcmp(name, "PATH") == 0)
		// recupath();
	// 	array_free(&std->path);
	// if (std->myenv)
	// 	env_list_destroy();
	if ((new = env_search(name)))
	{
		if (new->value)
			ft_strdel(&new->value);
		if (value)
			new->value = ft_strdup(value);
	}
	else
	{
		if (!(new = malloc(sizeof(t_env))))
			exit(-1);
		new->next = NULL;
		// while (head && head->next)
			// new = new->next
		new->name = ft_strdup(name);
		new->value = (value) ? ft_strdup(value) : NULL;
		add_right(new);
	}
}

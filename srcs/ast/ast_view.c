
#include "shell.h"

static void ft_print_graph(t_ast *ast, int n, int fd)
{
	char *color;
	char *command_line;
	
	color = ft_strdup(!ast->ret ? "color=green" : "color=red, style=filled");
	command_line = lexer_to_str(ast->lexer_node);
	my_printf("\t\tn%i [label=\"%s\",%s] ;\n", fd, n, command_line, color);
	free(command_line);
	free(color);
}

static int recurs(t_ast *ast, int n, int fd)
{
	int my_n;

	my_n = n;
	ft_print_graph(ast, n, fd);
	if (ast->right)
	{
		my_printf("\t\t\"n%i\" --  \"n%i\"\n", fd, my_n, my_n + 1);
		n = recurs(ast->right, my_n + 1, fd);
	}
	if (ast->left)
	{
		my_printf("\t\tn%i -- n%i [style=dotted] ;\n", fd, my_n, n + 1);
		n = recurs(ast->left, n + 1, fd);
	}
	return (n);
}


void graph(t_ast *ast)
{
	int fd;

	if (!ast)
	{
		ft_puterror("no ast for ast_view");
		return ;
	}
	remove("./graph"); // Replace with 
	if ((fd = open("./graph", O_WRONLY | O_APPEND | O_CREAT, 0755)) < 0)
	{
        my_printf("ERROR : open \"./graph\"\n", 2);
		exit(-1);
	}
	if (fd != -1)
		close(fd);
	my_printf("graph \"\"\n\t{\n\t\t", fd);
	recurs(ast, 0, fd);
	my_printf("\t}\n", fd);
	system("dot -Tpng graph > graph.png");
}

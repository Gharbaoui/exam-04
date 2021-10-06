#include "microshell.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		++i;
	return i;
}

void	print(char *str)
{
	write (ERR, str, ft_strlen(str));
}

void	func_err()
{
	print("error: fatal\n");
	exit(1);
}

char	*ft_strdup(char *str)
{
	char *tmp;
	int len;
	int i;

	i = -1;
	len = ft_strlen(str) + 1;
	tmp = malloc(len);
	if (!tmp)
		func_err();
	while (str[++i])
		tmp[i] = str[i];
	tmp[i] = 0;
	return tmp;
}


void	add_to_p(p_cmd **head, p_cmd **node)
{
	p_cmd *next;
	(*node)->next = NULL;
	if (*head)
	{
		next = *head;
		while (next->next)
			next = next->next;
		next->next = *node;
	}else{
		*head = *node;
	}
}
void	add_to_f(f_cmd **head, f_cmd **node)
{
	f_cmd *next;
	(*node)->next = NULL;
	if (*head)
	{
		next = *head;
		while (next->next)
			next = next->next;
		next->next = *node;
	}else{
		*head = *node;
	}
}

int	get_next_sep(int start, int end, char **args, char *sep)
{
	while (start < end){
		if (!strcmp(args[start], sep))
			return start;
		++start;
	}
	return start;
}

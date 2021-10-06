#include "microshell.h"


void	collect_data(f_cmd **cmd, int argc, char **argv)
{
	f_cmd *tmp;
	int start;

	start = 1;
	while (start < argc)
	{
		tmp = get_full_cmd(&start, argc, argv);
		add_to_f(cmd, &tmp);
	}
}

f_cmd	*get_full_cmd(int *start, int end, char **args)
{
	int	next_s, next_p;
	int i;
	f_cmd *fcmd;
	p_cmd	*pcmd;
	p_cmd	*tmp;

	pcmd = NULL;
	fcmd = malloc(sizeof(f_cmd));
	if (!fcmd)
		func_err();
	i = *start;
	next_s = get_next_sep(i, end, args, SEM);
	*start = next_s + 1;
	while (i < next_s)
	{
		next_p = get_next_sep(i, next_s, args, PIPE);
		tmp = get_one_cmd(i, next_p, args);
		add_to_p(&pcmd, &tmp);
		i = next_p + 1;
	}
	fcmd->cmd = pcmd;
	fcmd->next = NULL;
	return fcmd;
}

p_cmd	*get_one_cmd(int start, int end, char **args)
{
	p_cmd *tmp;
	int i;

	i = 0;
	tmp = malloc(sizeof(p_cmd));
	tmp->cmd = ft_strdup(args[start]);
	tmp->args = malloc(sizeof(char *) * (end - start + 1));
	tmp->args[end - start] = NULL;
	while (start < end)
	{
		tmp->args[i] = ft_strdup(args[start]);
		++i;
		++start;
	}
	return tmp;
}

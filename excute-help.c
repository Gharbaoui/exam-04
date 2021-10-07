#include "microshell.h"

int	get_num_cmds(p_cmd *cmd)
{
	int counter = -1;
	while (cmd)
	{
		++counter;
		cmd = cmd->next;
	}
	return counter;
}

void	excute_multi(p_cmd *cmd, int index, int max_index, char **envp, int p[2][2])
{
	int id;

	if (cmd)
	{
		make_pipes(p, index, max_index);
		id = fork();
		if (id == 0)
		{
			red_IO(index, max_index, p);
			execve(cmd->cmd, cmd->args, envp);
			exc_err(cmd->cmd);
		}
		excute_multi(cmd->next, index + 1, max_index, envp, p);
		waitpid(id, 0, 0);
	}
	close_both(p);
}

void	make_pipes(int p[2][2], int index, int max_index)
{
/*	if (index)
	{
		if (index % 2)
		{
			close(p[1][IN]);
			close(p[1][OUT]);
			if (index != max_index)
				pipe(p[1]);
		}else{
			close(p[0][IN]);
			close(p[0][OUT]);
			if (index != max_index)
				pipe(p[0]);
		}
	}*/
	if (index)
	{
		close(p[index % 2][IN]);
		close(p[index % 2][OUT]);
		if (index != max_index)
			pipe(p[index % 2]);
	}
}

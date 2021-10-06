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

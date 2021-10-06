#include "microshell.h"

void	excute(f_cmd *cmd, char **envp)
{
	while (cmd)
	{
		if (cmd->cmd)
			excute_one_f(cmd->cmd, envp);
		cmd = cmd->next;
	}
}

void	excute_one_f(p_cmd *cmd, char **envp)
{
	int p[2][2];
	int max_index;
	if (cmd->next)
	{
		// means at least one pipe
		max_index = get_num_cmds(cmd);
		pipe(p[0]);
		pipe(p[1]);
		excute_multi(cmd, 0, max_index, envp, p);
	}else{
		excute_none(cmd, envp);
	}
}

void	excute_none(p_cmd *cmd, char **envp)
{
	int id;

	if (strcmp(cmd->cmd, "cd"))
	{
		id = fork();
		if (id == 0)
		{
			execve(cmd->cmd, cmd->args, envp);
			exc_err(cmd->cmd);
		}
		waitpid(id, 0, 0);
	}else{
		cd_command(cmd);
	}
}

void	cd_command(p_cmd *cmd)
{
	if (cmd->args[1])
	{
		if (chdir(cmd->args[1])) {
			print("error: cd: cannot change directory to ");
			print(cmd->args[1]);
			print("\n");
		}
	}else{
		print("error: cd: bad arguments\n");
	}
}

void	exc_err(char *cmd)
{
	print("error: cannot execute ");
	print(cmd);
	print("\n");
}

void	red_IO(int index, int max_index, int p[2][2])
{
	if (index % 2)
	{
		if (index > 1)
		{
			close(p[1][IN]);
			close(p[1][OUT]);
			pipe(p[1]);
		}
		dup2(p[0][IN], IN);
		if (index != max_index)
			dup2(p[1][OUT], OUT);
	}else{
		if (index == max_index)
			dup2(p[1][IN], IN);
		else if (index)
		{
			close(p[0][IN]);
			close(p[0][OUT]);
			pipe(p[0]);
			dup2(p[1][IN], IN);
			dup2(p[0][OUT], OUT);
		}else{
			dup2(p[0][OUT], OUT);
		}
	}
	close_both(p);
}

void	close_both(int p[2][2])
{
	close(p[0][IN]);
	close(p[0][OUT]);
	close(p[1][IN]);
	close(p[1][OUT]);
}

#include "microshell.h"

void	print_full(f_cmd *cmd)
{
	while (cmd)
	{
		print("cmd\n");
		print_one(cmd->cmd);
		cmd = cmd->next;
	}	
}


void	print_one(p_cmd *cmd)
{
	while (cmd)
	{
		print_op(cmd);
		cmd = cmd->next;
	}
}

void	print_op(p_cmd *cmd)
{
	int i = -1;
	print(cmd->cmd);
	print ("  ");
	while (cmd->args[++i])
	{
		print(cmd->args[i]);
		print(" ");
	}
	print("\n");
}

#include "microshell.h"

int main(int argc, char **argv, char **envp)
{
	if (argc  > 1)
	{
		f_cmd *cmd;
		cmd = NULL;
		collect_data(&cmd, argc, argv);
		excute(cmd, envp);
	}
}

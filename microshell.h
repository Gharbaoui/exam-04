#ifndef MICRO_HPP
#define MICRO_HPP

#include <stdio.h> // remove later
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define ERR 2
#define OUT 1
#define IN 0

#define PIPE  "|"
#define SEM	  ";"

typedef	struct pcmd{
	char *cmd;
	char	**args;
	struct pcmd *next;
}	p_cmd;

typedef struct fcmd{
	p_cmd *cmd;
	struct fcmd *next;
}	f_cmd;


int ft_strlen(char *str);
void	print(char *str);
char	*ft_strdup(char *str);
void	add_to_p(p_cmd **head, p_cmd **node);
void	add_to_f(f_cmd **head, f_cmd **node);
int	get_next_sep(int start, int end, char **args, char *sep);
void	collect_data(f_cmd **cmd, int argc, char **argv);
f_cmd	*get_full_cmd(int *start, int end, char **args);
p_cmd	*get_one_cmd(int start, int end, char **args);
void	func_err();
void	print_op(p_cmd *cmd);
void	print_full(f_cmd *cmd);
void	print_one(p_cmd *cmd);
void	excute(f_cmd *cmd, char **envp);
void	excute_one_f(p_cmd *cmd, char **envp);
void	excute_none(p_cmd *cmd, char **envp);
void	cd_command(p_cmd *cmd);
void	exc_err(char *cmd);
int	get_num_cmds(p_cmd *cmd);
void	excute_multi(p_cmd *cmd, int index, int max_index, char **envp, int p[2][2]);
void	red_IO(int index, int max_index, int p[2][2]);
void	close_both(int p[2][2]);
void	make_pipes(int p[2][2], int index, int max_index);
#endif

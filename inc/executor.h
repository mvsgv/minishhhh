#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "Minishell.h"

typedef struct s_command t_command; 

int is_builtin(t_command *cmd);
int execute_builtin(t_command *cmd);
int handle_infile(t_command *cmd);
int handle_outfile(t_command *cmd);
void execute_command(t_command *cmd);
void execute_all_commands(t_command *cmds);



#endif
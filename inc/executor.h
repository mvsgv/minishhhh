#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "Minishell.h"

typedef struct s_command t_command; 
typedef struct s_env t_env;

int is_builtin(t_command *cmd);
int execute_builtin(t_command *cmd, t_env *env);
void execute_command(t_command *cmd, t_env *env);
int handle_infile(t_command *cmd);
int handle_outfile(t_command *cmd);
void execute_all_commands(t_command *cmds, t_env *env);
void execute_pipeline(t_command *cmds, t_env *env);
void sigint_handler(int sig);
void setup_signals(void);
void child_process(t_command *cmd, int **pipes, int i, t_env *env);
void wait_and_cleanup(int **pipes, pid_t *pids, int n, t_env *env);
int setup_pipes_and_fork(t_command *cmds, t_env *env, int **pipes, pid_t *pids);
int count_cmds(t_command *cmds);

#endif
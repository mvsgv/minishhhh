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
// void wait_and_cleanup(int **pipes, pid_t *pids, int n, t_env *env);
// int setup_pipes_and_fork(t_command *cmds, t_env *env, int **pipes, pid_t *pids);
int count_cmds(t_command *cmds);

char *get_command_path(char *cmd, t_env *env);
void free_split(char **tab);
char *path_join(const char *dir, const char *file);
void execute_child_process(t_command *cmd, t_env *env);
void wait_and_cleanup(int **pipes, pid_t *pids, int n, t_env *env);
void cleanup_memory(int **pipes, pid_t *pids, int n);
int create_all_pipes(int **pipes, int num_cmds);
int fork_all_processes(t_command *cmds, int **pipes, pid_t *pids, t_env *env);
void close_all_pipes_parent(int **pipes);


#endif
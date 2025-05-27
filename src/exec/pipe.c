#include "../../inc/executor.h"

void child_process(t_command *cmd, int **pipes, int i, t_env *env)
{
	int	j;
	int	status;

	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < count_cmds(cmd) - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	status = handle_infile(cmd);
	if (status == 0)
		status = handle_outfile(cmd);
	if (status == 0 && is_builtin(cmd))
		exit(execute_builtin(cmd, env));
	else if (status == 0)
        execve(cmd->args[0], cmd->args, env->envp);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
}

void wait_and_cleanup(int **pipes, pid_t *pids, int n, t_env *env)
{
	int	i;
	int	status;

	i = -1;
	while (++i < n - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1)
		{
			if (WIFEXITED(status))
				env->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				env->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(pids);
}

int setup_pipes_and_fork(t_command *cmds, t_env *env, int **pipes, pid_t *pids)
{
	t_command	*cur;
	int			i;

	cur = cmds;
	i = 0;
	while (cur && i < count_cmds(cmds) - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
			return (1);
		i++;
	}
	i = 0;
	cur = cmds;
	while (cur)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			return (child_process(cur, pipes, i, env), 0);
		else if (pids[i] < 0)
			return (1);
		cur = cur->next;
		i++;
	}
	return (0);
}

void execute_pipeline(t_command *cmds, t_env *env)
{
	int			num_cmds;
	int			**pipes;
	pid_t		*pids;

	num_cmds = 0;
	pipes = NULL;
	pids = NULL;
	num_cmds = count_cmds(cmds);
	if (num_cmds == 1)
		return (execute_command(cmds, env));
	pipes = malloc(sizeof(int *) * (num_cmds - 1));
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pipes || !pids)
		return (free(pipes), free(pids));
	if (setup_pipes_and_fork(cmds, env, pipes, pids))
		return (wait_and_cleanup(pipes, pids, num_cmds, env));
}

void execute_all_commands(t_command *cmds, t_env *env)
{
    if (!cmds)
        return;
    execute_pipeline(cmds, env);
}
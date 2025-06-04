#include "../../inc/executor.h"

void	cleanup_memory(int **pipes, pid_t *pids, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(pids);
}

void	wait_and_cleanup(int **pipes, pid_t *pids, int n, t_env *env)
{
	int	i;
	int	status;

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
	cleanup_memory(pipes, pids, n);
}

void	close_all_pipes_parent(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	child_process(t_command *cmd, int **pipes, int i, t_env *env)
{
	int	j;

	if (handle_infile(cmd) != 0)
		exit(1);
	if (handle_outfile(cmd) != 0)
		exit(1);
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (pipes[j])
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd))
		exit(execute_builtin(cmd, env));
	else
		execute_child_process(cmd, env);
}

int	fork_all_processes(t_command *cmds, int **pipes, pid_t *pids, t_env *env)
{
	t_command	*cur;
	int		i;

	cur = cmds;
	i = 0;
	while (cur)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			child_process(cur, pipes, i, env);
		if (pids[i] < 0)
			return (-1);
		cur = cur->next;
		i++;
	}
	return (0);
}

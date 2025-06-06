/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:21:58 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/05 17:43:17 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"

static void	cleanup_failed_setup(int **pipes, pid_t *pids, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
	free(pids);
}

static void	handle_parent_process(pid_t pid, t_env *env)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		env->exit_status = 128 + WTERMSIG(status);
}

void	execute_command(t_command *cmd, t_env *env)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (cmd->args[0][0] == '\0')
	{
		env->exit_status = 127;
		return ;
	}
	if (is_builtin(cmd) && !cmd->next)
	{
		execute_builtin_no_fork(cmd, env);
		return ;
	}
	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, env);
	else if (pid > 0)
		handle_parent_process(pid, env);
	else
	{
		perror("fork");
		env->exit_status = 1;
	}
}

void	execute_pipeline(t_command *cmds, t_env *env)
{
	int		num_cmds;
	int		**pipes;
	pid_t	*pids;

	num_cmds = count_cmds(cmds);
	if (num_cmds == 1)
		return (execute_command(cmds, env));
	pipes = malloc(sizeof(int *) * num_cmds);
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pipes || !pids)
		return (free(pipes), free(pids));
	if (create_all_pipes(pipes, num_cmds) < 0)
		return (cleanup_failed_setup(pipes, pids, num_cmds - 1));
	if (fork_all_processes(cmds, pipes, pids, env) < 0)
		return (cleanup_failed_setup(pipes, pids, num_cmds - 1));
	close_all_pipes_parent(pipes);
	wait_and_cleanup(pipes, pids, num_cmds, env);
}

void	execute_all_commands(t_command *cmds, t_env *env)
{
	if (!cmds)
		return ;
	execute_pipeline(cmds, env);
}

#include "../../inc/executor.h"

int	execute_builtin(t_command *cmd, t_env *env)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		status = builtin_cd(cmd->args, env);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		status = builtin_exit(cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		status = builtin_pwd(env);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		status = builtin_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		status = builtin_env(env);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		status = builtin_export(cmd->args, env);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		status = builtin_unset(cmd->args, env);
	env->exit_status = status;
	return (status);
}

void	execute_builtin_no_fork(t_command *cmd, t_env *env)/////EXIT
{
	int	status;
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	status = handle_infile(cmd);
	if (status == 0)
		status = handle_outfile(cmd);
	if (status == 0)
		status = execute_builtin(cmd, env);
	if (stdin_backup >= 0)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup >= 0)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
	env->exit_status = status;
}

int	is_builtin(t_command *cmd)
{
	if (cmd->args && cmd->args[0])
	{
		if (ft_strcmp(cmd->args[0], "cd") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "echo") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "env") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "unset") == 0)
			return (1);
	}
	return (0);
}

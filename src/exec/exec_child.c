/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:22:12 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 21:25:16 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/executor.h"
#include "../../inc/builtins.h"

char	*path_join(const char *dir, const char *file)
{
	char	*full_path;
	int		len_dir;
	int		len_file;
	int		i;

	len_dir = 0;
	len_file = 0;
	while (dir[len_dir])
		len_dir++;
	while (file[len_file])
		len_file++;
	full_path = malloc(len_dir + len_file + 2);
	if (!full_path)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	copy_str(full_path, dir, &i);
	if (i > 0 && full_path[i - 1] != '/')
		full_path[i++] = '/';
	copy_str(full_path, file, &i);
	full_path[i] = '\0';
	return (full_path);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = path_join(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*env_get(t_env *env, const char *name)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], name, name_len) == 0
			&& env->envp[i][name_len] == '=')
			return (env->envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = env_get(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_split(paths);
	return (result);
}

void	execute_child_process(t_command *cmd, t_env *env)
{
	char	*cmd_path;

	if (handle_infile(cmd) != 0)
		exit(1);
	if (handle_outfile(cmd) != 0)
		exit(1);
	if (is_builtin(cmd))
		exit(execute_builtin(cmd, env));
	cmd_path = get_command_path(cmd->args[0], env);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	execve(cmd_path, cmd->args, env->envp);
	perror("execve");
	free(cmd_path);
	exit(1);
}

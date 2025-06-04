/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:21:02 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 21:21:04 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"

//CD    

static int	update_pwd_oldpwd(t_env *env, char *old_pwd)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (!tmp)
		return (1);
	env_set(env, tmp);
	free(tmp);
	if (getcwd(old_pwd, 1024) == NULL)
	{
		perror("cd: getcwd error");
		return (1);
	}
	tmp = ft_strjoin("PWD=", old_pwd);
	if (!tmp)
		return (1);
	env_set(env, tmp);
	free(tmp);
	return (0);
}

static char	*get_cd_path(char **args, t_env *env)
{
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		if (!env->home)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (env->home);
	}
	return (args[1]);
}

static char	*handle_cd_dash(t_env *env)
{
	char	*path;

	path = env_get(env, "OLDPWD");
	if (!path)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return (NULL);
	}
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (path);
}

int	builtin_cd(char **args, t_env *env)
{
	char	old_pwd[1024];
	char	*path;

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("cd: getcwd error");
		return (1);
	}
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		path = handle_cd_dash(env);
	else
		path = get_cd_path(args, env);
	if (!path || chdir(path) != 0)
	{
		if (path)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			perror(path);
		}
		return (1);
	}
	return (update_pwd_oldpwd(env, old_pwd));
}

//PWD   

int	builtin_pwd(t_env *env)
{
	char	*pwd_env;
	char	cwd[1024];

	pwd_env = env_get(env, "PWD");
	if (pwd_env)
	{
		ft_putstr_fd(pwd_env, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("pwd");
			return (1);
		}
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
}

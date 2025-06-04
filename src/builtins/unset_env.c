#include "../../inc/builtins.h"

//UNSET

static int	find_env_index(char **envp, const char *name)
{
	size_t	i;
	size_t	name_len;
	size_t	current_len;
	char	*equal_sign;

	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
			current_len = (size_t)(equal_sign - envp[i]);
		else
			current_len = ft_strlen(envp[i]);
		if (ft_strncmp(envp[i], name, name_len) == 0 && current_len == name_len)
			return ((int)i);
		i++;
	}
	return (-1);
}

void	env_unset(t_env *env, const char *name)
{
	int	i;

	i = find_env_index(env->envp, name);
	if (i < 0)
		return ;
	free(env->envp[i]);
	while (env->envp[i + 1])
	{
		env->envp[i] = env->envp[i + 1];
		i++;
	}
	env->envp[i] = NULL;
	if (ft_strcmp(name, "HOME") == 0)
	{
		free(env->home);
		env->home = NULL;
	}
}

int	builtin_unset(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			i++;
			continue ;
		}
		env_unset(env, args[i]);
		i++;
	}
	return (0);
}

int	builtin_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		ft_putstr_fd(env->envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (0);
}

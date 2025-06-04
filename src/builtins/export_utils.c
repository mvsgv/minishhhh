#include "../../inc/builtins.h"

int	env_set_existing(t_env *env, char *var, char *name, char *equal_sign)
{
	int	i;
	char	*existing_equal;
	size_t	name_len;

	i = 0;
	while (env->envp[i])
	{
		existing_equal = ft_strchr(env->envp[i], '=');
		if (existing_equal)
			name_len = (size_t)(existing_equal - env->envp[i]);
		else
			name_len = ft_strlen(env->envp[i]);
		if (ft_strncmp(env->envp[i], name, name_len) == 0
			&& ft_strlen(name) == name_len)
		{
			if (equal_sign)
			{
				free(env->envp[i]);
				env->envp[i] = ft_strdup(var);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	env_add_new(t_env *env, char *var, char *name, char *equal_sign)
{
	int	i;
	int	j;
	char	**new_envp;

	i = 0;
	while (env->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (0);
	j = 0;
	while (j < i)
	{
		new_envp[j] = env->envp[j];
		j++;
	}
	if (equal_sign)
		new_envp[i] = ft_strdup(var);
	else
		new_envp[i] = ft_strdup(name);
	new_envp[i + 1] = NULL;
	free(env->envp);
	env->envp = new_envp;
	return (1);
}

void	update_home_if_needed(t_env *env, char *name, char *value)
{
	if (ft_strcmp(name, "HOME") == 0)
	{
		free(env->home);
		env->home = ft_strdup(value);
	}
}

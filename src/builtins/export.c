/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:21:35 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 21:24:17 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	print_export_var(char *var)
{
	char	*equal_sign;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	equal_sign = ft_strchr(var, '=');
	if (equal_sign)
	{
		write(STDOUT_FILENO, var, equal_sign - var);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(equal_sign + 1, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(var, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

void	ft_sort_strarr(char **arr)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	len = 0;
	while (arr[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static int	export_no_args(t_env *env)
{
	int		i;
	char	**envp_copy;

	envp_copy = ft_arrdup(env->envp);
	if (!envp_copy)
		return (1);
	ft_sort_strarr(envp_copy);
	i = 0;
	while (envp_copy[i])
	{
		print_export_var(envp_copy[i]);
		i++;
	}
	ft_free_arr(envp_copy);
	return (0);
}

int	builtin_export(char **args, t_env *env)
{
	int	i;

	i = 1;
	if (!args[1])
		return (export_no_args(env));
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			i++;
			continue ;
		}
		env_set(env, args[i]);
		i++;
	}
	return (0);
}

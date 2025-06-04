/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:00:35 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 21:27:50 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "Minishell.h"
# include "executor.h"
# include <stdbool.h>

typedef struct s_env
{
	char	**envp; // Environment variables array
	char	*home; // HOME environment variable value
	int		exit_status; // Last command exit status
}		t_env;

int		builtin_echo(char **args);
int		builtin_cd(char **args, t_env *env);
// int builtin_pwd(void);
int		builtin_pwd(t_env *env);
int		builtin_exit(char **args);
int		builtin_export(char **args, t_env *env);
int		builtin_unset(char **args, t_env *env);
void	env_set(t_env *env, char *var);
void	env_unset(t_env *env, const char *name);
char	*env_get(t_env *env, const char *name);
int		builtin_env(t_env *env);
t_env	*env_init(char **envp);
void	env_free(t_env *env);
char	**ft_arrdup(char **arr);
void	ft_free_arr(char **arr);
void	ft_sort_strarr(char **arr);
bool	is_valid_identifier(const char *str);
void	increment_shlvl(t_env *env);
void	set_var_with_value(t_env *env, char *var, char *name, char *equal_sign);
void	set_var_without_value(t_env *env, char *name);
int		env_set_existing(t_env *env, char *var, char *name, char *equal_sign);
int		env_add_new(t_env *env, char *var, char *name, char *equal_sign);
void	update_home_if_needed(t_env *env, char *name, char *value);

#endif
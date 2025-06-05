/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:54:49 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/05 17:24:14 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

/*
EXIT_CODE_EXPAND
Handles the case $?
Converts the int into a string, joins it, frees the old strings
Before:
exit_code = 127
result    = "Command failed with code: "
After:
val = ft_itoa(exit_code); --> converts 127 to "127" --> val = "127"
tmp = ft_strjoin(result, val);
Concatenates "Command failed with code: " + "127"
tmp = "Command failed with code: 127"
*/
/*
ENV_VAR_EPANSION
1) Extract the variable name
2)Extract the variable name
3)Get the value of the variable
4)Duplicate the value (do not include anything before the variable)
str → the input line (e.g. "echo $USER")
i → pointer to the current index in the string
env → your environment list (t_env)
res → the result string built so far (e.g., "echo ")
Let’s say:
str = "echo $USER"

*i = 5 (points to the U after $)

env contains USER=mavissar

res = "echo " (space included)
*/

/*APPEND_CHAR_TO_RES
Its job is to add one character (the current str[i])
to a growing result string res.
char		tmp[2] = {str[i], 0};
str[i] = 'c'     →    tmp = ['c', '\0']     →    tmp = "c"
comme je itere i dans ma fonction principale,
mon caractere change et le prochain
se rajoute
Is used when there’s no special $ expansion needed
Is memory-safe (free(res))
Ensures quote handling or $ logic doesn’t interfere
*/
static int	handle_exit_code(int *i, t_expand_data *data)
{
	*data->res = exit_code_expand(i, data->exit_cd, *data->res);
	if (!*data->res)
		return (1);
	return (0);
}

static int	handle_env_var(const char *str, int *i, t_expand_data *data)
{
	char	*tmp;
	char	*new_res;

	tmp = env_var_expansion(str, i, data->env);
	if (!tmp)
	{
		free(*data->res);
		return (1);
	}
	new_res = ft_strjoin(*data->res, tmp);
	free(*data->res);
	free(tmp);
	*data->res = new_res;
	if (!*data->res)
		return (1);
	return (0);
}

static int	handle_dollar(const char *str, int *i, t_expand_data *data)
{
	if (str[*i + 1] == '?')
		return (handle_exit_code(i, data));
	else
		return (handle_env_var(str, i, data));
}

static int	process_char(const char *str, int *i, t_expand_data *data,
		int *in_sq)
{
	if (str[*i] == '$' && !*in_sq)
	{
		if (handle_dollar(str, i, data))
			return (1);
	}
	else
	{
		*data->res = append_char_to_res(*data->res, str[*i]);
		if (!*data->res)
			return (1);
		(*i)++;
	}
	return (0);
}

char	*expand_word(const char *str, t_env *env, int exit_cd)
{
	int				i;
	int				in_sq;
	int				in_dq;
	t_expand_data	data;

	i = 0;
	in_dq = 0;
	in_sq = 0;
	data.res = malloc(sizeof(char *));
	*data.res = ft_calloc(1, 1);
	data.env = env;
	data.exit_cd = exit_cd;
	if (!*data.res)
		return (NULL);
	while (str[i])
	{
		dq_sq(str[i], &in_sq, &in_dq);
		if (process_char(str, &i, &data, &in_sq))
			return (NULL);
	}
	return (*data.res);
}

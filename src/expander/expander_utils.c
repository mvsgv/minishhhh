/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:19:01 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/05 17:20:24 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

char	*exit_code_expand(int *i, int exit_cd, char *res)
{
	char	*val;
	char	*tmp;

	(*i)++;
	val = ft_itoa(exit_cd);
	tmp = ft_strjoin(res, val);
	free(val);
	free(res);
	return (tmp);
}

char	*env_var_expansion(const char *str, int *i, t_env *env)
{
	char	*key;
	char	*val;
	char	*tmp;
	int		start;

	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	if (!key)
		return (NULL);
	val = get_env_value(key, env);
	tmp = ft_strdup(val);
	free(key);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*append_char_to_res(char *res, char c)
{
	char	tmp[2];
	char	*join;

	tmp[0] = c;
	tmp[1] = '\0';
	join = ft_strjoin(res, tmp);
	free(res);
	res = join;
	return (res);
}

void	dq_sq(char c, int *in_sq, int *in_dq)
{
	if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
	else if (c == '\"' && !(*in_sq))
		*in_dq = !(*in_dq);
}

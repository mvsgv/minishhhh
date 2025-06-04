/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:52:49 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 16:58:29 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"

static int	word_count(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*make_tab(const char *start, const char *end)
{
	char	*str;
	int		i;

	str = (char *)malloc(end - start + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = *start++;
	str[i] = '\0';
	return (str);
}

static int	if_dont_work(char **result, int i)
{
	if (!result[i - 1])
	{
		ft_free(result);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	const char	*start;
	int			i;

	i = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			continue ;
		start = s;
		while (*s && *s != c)
			s++;
		result[i++] = make_tab(start, s);
		if (if_dont_work(result, i))
			return (NULL);
	}
	result[i] = NULL;
	return (result);
}

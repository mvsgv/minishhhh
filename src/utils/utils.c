/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augeerae <augeerae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:34:28 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/27 12:52:57 by augeerae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"

char    *ft_strndup(char *line, int start, int end)
{
    int len;
    char    *str;

    len = end - start;
    str = malloc(len + 1);
    if (!len)
        return (NULL);
    ft_memcpy(str, &line[start], len);
    str[len] = '\0';
    return (str);
}


int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			break ;
		i++;
	}
	if (s[i] == (char) c)
		return ((char *) s + i);
	return (NULL);
}

static void	ft_free(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free (arr[i]);
			i++;
		}
		free(arr);
	}
}

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

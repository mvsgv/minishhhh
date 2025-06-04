/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:09:01 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 20:09:28 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	pipe_counter(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while (line[i])
	{
		if (line[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	**split_pipes(char *line)
{
	int		i;
	int		start;
	int		end;
	char	**res;

	end = 0;
	i = 0;
	start = 0;
	res = malloc(sizeof(char *) * (pipe_counter(line) + 1));
	while (line[end])
	{
		if (line[end] == '|')
		{
			res[i++] = ft_strndup(line, end, start);
			end++;
			while (line[end] == ' ')
				end++;
			start = end;
		}
		else
			end++;
	}
	return (res);
}

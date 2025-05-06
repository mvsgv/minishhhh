/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:34:28 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/06 18:07:19 by mavissar         ###   ########.fr       */
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

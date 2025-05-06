/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:09:01 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/06 18:35:05 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"

static int     pipe_counter(char *line)
{
    int count;
    int i;
    
    i = 0;
    count = 1; // car meme si pas de pipe sur la ligne on aura toujout une commande a executer 
    while (line[i])
    {
        if (line[i] == '|')
        count++;
    }
    return (count);
}


char    **split_pipes(char *line)
{
    int i;
    int start;
    int end;
    int nb_cmds;
    char    **res;
    
    end = 0;
    i = 0;
    start = 0;
    nb_cmds = pipe_counter(line);
    res = malloc(sizeof(char*) * (nb_cmds + 1));
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
    return res;
}

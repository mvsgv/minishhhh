/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:18:42 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/02 17:17:36 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minishell.h"

//si j enchaine plus de deux operateurs de suite cést qu il y a un pb d input
bool    invalid_op(const char *line)
{
    while (*line)
    {
        if ((*line == '|' && *(line + 1) == '|' && *(line + 2) == '|') || 
            (*line == '>' && *(line + 1) == '>' && *(line + 2) == '>') || 
            (*line == '<' && *(line + 1) == '<' && *(line + 2) == '<'))
                return true;
            line++;
    }
    return false;
}

bool    has_closed_quotes(const char *line)
{
    int i;
    
    i = 0;
    while (*line == ' ')
        line++;
    if (*line == '|')
        return (true); // 2
    while (line[i])
        i++;
    i--;
    while (i >= 0 && line[i] == ' ') // move i back to skip trailing spaces  
        i--;
    return(line[i] == '|'); // Is that last character a pipe if yes theen 2
}


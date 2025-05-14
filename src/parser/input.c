/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:18:42 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/14 14:31:36 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//si j enchaine plus de deux operateurs de suite cést qu il y a un pb d input
static bool    invalid_op(const char *line)
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

static int quotes_checker(const char *line)
{
    int single_qt;
    int double_qt;

    single_qt = 0;
    double_qt = 0;
    while(*line)
    {
        if (*line == '\'')
            single_qt++;
        if (*line == '\"')
            double_qt++;
        line++;
    }
    return (single_qt % 2 == 0 && double_qt % 2 == 0); // true or false
}

static bool    pipe_err(const char *line)
{
    int i;
    
    i = 0;
    while (line[i])
    {
        if (line[i] == '|')
        {
            i++;
            while (line[i] && isspace(line[i]))
                i++;
            if (line[i] == '|' || line[i] == '\0')
            return (true);
        }
        else 
            i++;
    }
    i--;
    while (i >= 0 && isspace(line[i]))
        i--;
    return (line[i] == '|');
    }

bool    input_checker(const char *line)
{
    int i;

    i = 0;
    while (line[i] && isspace(line[i]))
        i++;
    if (line[i] == '|')
    {
        printf("bash: syntax error near unexpected token `|'\n");
        return false;
    }
    if (pipe_err(line))
    {
        printf("bash: syntax error: unexpected token\n");
		return false;
    }
    if (invalid_op(line))
    {
        printf("bash: syntax error: unexpected token\n");
		return false;
    }
	if (!quotes_checker(line))
	{
		printf("bash: syntax error: unclosed quote\n");
		return false;
	}
    return true;
}


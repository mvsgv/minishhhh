/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:45:45 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/12 17:44:21 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"

void    handle_word(const char *line, int *i, t_token **list)
{
    int     start;
    char    *word;
    
    start = *i;
    while (line[*i] && !ft_isspace(line[*i]) && 
    line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
        (*i)++;
    if (*i >= (int)ft_strlen(line))//to ensure *i doesnt overflows the string
        return;
    word = ft_substr(line, start, *i - start);
    add_token(list, word, WORD);
    free(word);
}

void    handle_operator(const char *line, int *i, t_token **list)
{
    int     start;
    char    *operator;

    start  = *i;
    if (line[*i] && line[*i + 1] && line[*i] == line[*i + 1])
        (*i)++;
    (*i)++;
    operator = ft_substr(line, start, *i - start);
    add_token(list, operator, get_token_type(operator));
    free(operator);
}
static char    *find_quotes(const char *line, int *i)
{
    char    quote;
    int     start;

    start = *i;
    quote = line[*i];
    while (line[*i] && line[*i] != quote)
        (*i)++;
    if (line[*i] == quote)
        (*i)++; // skip to the closing quote
    return (ft_substr(line, start, *i - start));
}

void    handle_quote(const char *line, int *i, t_token **list)
{
    char    *word;
    
    word = find_quotes(line, i);
    add_token(list, word, WORD);
    free(word);
}

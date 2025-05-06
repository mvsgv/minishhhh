/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:17 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/06 18:47:23 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"
#include "../../Libft/libft.h"

t_token_type get_token_type(const char *s)
{
    if (strcmp(s, "|") == 0) 
        return PIPE;
    if (strcmp(s, "<") == 0)
        return RED_IN;
    if (strcmp(s, ">") == 0)
        return RED_OUT;
    if (strcmp(s, "<<") == 0)
        return HEREDOC;
    if (strcmp(s, ">>") == 0)
        return APPEND;
    return WORD;
}

t_token *create_token(char *value , t_token_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = ft_strdup(value);
    token->type = type;
    token->next = NULL;
    return (token);
}

void    add_token(t_token **list, char *value, t_token_type type)
{
    t_token *new;
    
    new = create_token(value, type);
    if (!new)
        return ;
    if (!*list)
        *list = new;
    else
    {
        t_token *tmp = *list;
        tmp = tmp->next;
        tmp->next = new;
    }
}
t_token *lexer(const char *line)
{
    t_token *list;
    int i;
    int start;
    char    *word;
    char    *op;
    
    i = 0;
    list = NULL;
    while (line[i])
    {
        if (isspace(line[i]))
            i++;
        else if (line[i] == '|' || line[i] == '<' || line[i] == '<')
        {
            start = i;
            if (line[i + 1] == line[i])
                ++i;
            i++;
            op = ft_substr(line, start, i - start);
            add_token(&list, op, get_token_type(op));
            free(op);
       }
       else
       {
            start = i;
            while (line[i] && !isspace(line[i]) && 
            line[i] != '|' && line[i] != '<' && line[i] != '>')
            i++;
			word = ft_substr(line, start, i - start);
			add_token(&list, word, WORD);
			free(word);           
        }
    }
    return (list);
}

void    free_tok(t_token *list)
{
    while (list)
    {
        t_token *next = list->next;
        free(list->value);
        free(list);
        list = next;
    }
}

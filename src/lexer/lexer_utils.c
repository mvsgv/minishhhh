/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:45:45 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/14 14:31:59 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

// ┌──────────────┐      ┌──────────────┐      ┌────────────┐      ┌──────────────┐      ┌──────────┐      ┌────────────┐      ┌──────────────┐
// │  "echo"      │ ---> │  "hello"     │ ---> │    "|"     │ ---> │   "grep"     │ ---> │  "foo"   │ ---> │    ">"     │ ---> │  "out.txt"   │
// │  WORD        │      │  WORD        │      │   PIPE     │      │   WORD       │      │  WORD    │      │  RED_OUT   │      │   WORD       │
// └──────────────┘      └──────────────┘      └────────────┘      └──────────────┘      └──────────┘      └────────────┘      └──────────────┘
/*Chaque bloc a trois parties :
    - value → la chaîne de caractères du token (ex: "echo")
    - type → le type du token (ex: WORD, PIPE, RED_OUT)
    - next → un pointeur vers le prochain token*/

/*Retourne le type de token correspondant a la chaine,
    si ce n est pas un operateur connu on le considere comme WORD*/
t_token_type get_token_type(const char *s)
{
    if (ft_strncmp(s, "|", 1) == 0)
        return PIPE;
    if (ft_strncmp(s, "<", 1) == 0)
        return RED_IN;
    if (ft_strncmp(s, ">", 1) == 0)
        return RED_OUT;
    if (ft_strncmp(s, "<<", 1) == 0)
        return HEREDOC;
    if (ft_strncmp(s, ">>", 1) == 0)
        return APPEND;
    return WORD;
}

/*Cree un nouveau token avec la valeur et le type.
    Alloue dynamiquement la memoire pour le token et sa valeur*/
t_token *create_token(char *value, t_token_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = ft_strdup(value); // dupplique la chaine
    token->type = type;
    token->next = NULL;
    return (token);
}

/*Ajoute un nouveau token a la fin de la liste chainee
    Si la liste est vide le token devient le premier element*/
void add_token(t_token **list, char *value, t_token_type type)
{
    t_token *new;

    new = create_token(value, type);
    if (!new)
        return;
    if (!*list)
        *list = new;
    else
    {
        t_token *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

void free_tok(t_token *list)
{
    while (list)
    {
        t_token *next = list->next;
        free(list->value);
        free(list);
        list = next;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:17 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/08 16:17:28 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"
#include "../../Libft/libft.h"

//┌──────────────┐      ┌──────────────┐      ┌────────────┐      ┌──────────────┐      ┌──────────┐      ┌────────────┐      ┌──────────────┐
//│  "echo"      │ ---> │  "hello"     │ ---> │    "|"     │ ---> │   "grep"     │ ---> │  "foo"   │ ---> │    ">"     │ ---> │  "out.txt"   │
//│  WORD        │      │  WORD        │      │   PIPE     │      │   WORD       │      │  WORD    │      │  RED_OUT   │      │   WORD       │
//└──────────────┘      └──────────────┘      └────────────┘      └──────────────┘      └──────────┘      └────────────┘      └──────────────┘
/*Chaque bloc a trois parties :
    - value → la chaîne de caractères du token (ex: "echo")
    - type → le type du token (ex: WORD, PIPE, RED_OUT)
    - next → un pointeur vers le prochain token*/


/*Retourne le type de token correspondant a la chaine, 
    si ce n est pas un operateur connu on le considere comme WORD*/
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

/*Cree un nouveau token avec la valeur et le type.
    Alloue dynamiquement la memoire pour le token et sa valeur*/
t_token *create_token(char *value , t_token_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = ft_strdup(value);//dupplique la chaine
    token->type = type;
    token->next = NULL;
    return (token);
}

/*Ajoute un nouveau token a la fin de la liste chainee
    Si la liste est vide le token devient le premier element*/
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
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

/*Analyse ma ligne de commande et retourne une liste de token*/
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
        else if (line[i] == '|' || line[i] == '<' || line[i] == '<') //si je sis sur un operateur | < > << >>
        {
            start = i;
            if (line[i + 1] == line[i]) // cas de >> ou <<
                ++i;
            i++;
            op = ft_substr(line, start, i - start); //recupere l operateur 
            add_token(&list, op, get_token_type(op)); // stockage dans la liste
            free(op);
       }
       else//sinon cest un mot 
       {
            start = i;
            while (line[i] && !isspace(line[i]) && 
            line[i] != '|' && line[i] != '<' && line[i] != '>')//javance jusqua un espace ou unn operateur
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

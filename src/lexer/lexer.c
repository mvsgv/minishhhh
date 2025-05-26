/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:17:17 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/26 20:10:23 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Systeme de tri : Tokenization/Lexer
Transforme une entree d'utilisateur et les structures en tokens
ex: echo "hello" | grep hello > file.txt
valeur : echo , type = WORD 
valeur : | , type = PIPE
vaeur : > | type = RED_OUT
Il est important de faire la partie lexer avant la partie parser car le parser
attend une liste de tokens et non une string
Le parser lui construit une structure de commande (liste chainee de commandes)
et assigne les redirection, arguments, etc. Mais pour y arriver il aura besoin
de connaitre au minimum le nom des commandes, ce qu'est une argument ainsi 
qu'un operateur. Si je n'ai pas de lexer, mon parser n'aura pas de syntax.


INPUT : echo "$HOME"
Lexer turns input into tokens ($USER becomes one token)
    lexer creates { value: "$HOME", type: WORD }
Expander replaces values inside tokens
    expander turns into { value: "/home/mavissar", type: WORD }
Parser builds the command tree using final values
    parser sees command: echo
                args: ["/home/mavissar"]
                
If you expand before lexing, you'd break quotes/syntax.
If you expand after parsing, it's too late (parser might make wrong structure).

Lexer	    Breaks raw input into tokens (echo, >, etc.)
Expander	Replaces $VAR, $?, inside tokens
Parser  	Builds the command list (structure, pipes)*/

#include "../../inc/lexer.h"

static void handle_word(const char *line, int *i, t_token **list)
{
    int start;
    char *word;

    start = *i;
    while (line[*i] && !ft_isspace(line[*i]) &&
           line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
        (*i)++;
    word = ft_substr(line, start, *i - start);
    add_token(list, word, WORD);
    free(word);
}

static void handle_operator(const char *line, int *i, t_token **list)
{
    int start;
    char *operator;

    start = *i;
    if (line[*i] && line[*i + 1] && line[*i] == line[*i + 1])
        (*i)++;
    (*i)++;
    operator = ft_substr(line, start, *i - start);
    add_token(list, operator, get_token_type(operator));
    free(operator);
}

static char *find_quotes(const char *line, int *i)
{
    char quote;
    int start;
    char    *res;

    quote = line[*i];//storing th quote character in quote
    (*i)++;
    start = *i;//start point to the first character after the quote
    while (line[*i] && line[*i] != quote)
        (*i)++;
    res = ft_substr(line, start, *i - start);        
    if (line[*i] == quote)
        (*i)++; // skip to the closing quote
    return (res);
}

static void handle_quote(const char *line, int *i, t_token **list)
{
    char *word;

    word = find_quotes(line, i);
    add_token(list, word, WORD);
    free(word);
}

t_token *lexer(const char *line)
{
    t_token *list;
    int i;

    i = 0;
    list = NULL;
    while (line[i])
    {
        if (ft_isspace(line[i]))
            i++;
        else if (line[i] == '\'' || line[i] == '\"')
            handle_quote(line, &i, &list);
        else if (line[i] == '|' || line[i] == '<' || line[i] == '>') // si je sis sur un operateur | < > << >>
            handle_operator(line, &i, &list);
        else
            handle_word(line, &i, &list);
    }
    return (list);
}

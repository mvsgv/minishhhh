/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:20:43 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/27 21:53:49 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include "Minishell.h"

typedef struct s_env t_env;

typedef enum e_token_type
{
    WORD,
    PIPE,    // |
    RED_IN,  // <
    RED_OUT, // >
    HEREDOC, //<<
    APPEND   // >>
} t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
}   t_token;

t_token *lexer(const char *line, t_env *env, int exit_code);
t_token_type    get_token_type(const char *s);
t_token         *create_token(char *value , t_token_type type);
void            add_token(t_token **list, char *value, t_token_type type);
void            free_tok(t_token *list);
char            *expand_word(const char *str, t_env *env, int exit_cd);
char            *get_env_value(char *name, t_env *env);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:27:20 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/08 18:13:41 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#endif

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

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
    char *value;
    t_token_type type;
    struct s_token *next;
} t_token;

/*parser*/
char **split_pipes(char *line);
bool input_checker(const char *line);

/*lexer*/
t_token *lexer(const char *line);
t_token_type get_token_type(const char *s);
t_token *create_token(char *value, t_token_type type);
void add_token(t_token **list, char *value, t_token_type type);
void free_tok(t_token *list);

/*utils*/
char *ft_strndup(char *line, int start, int end);

/*quotes*/
int quotes_checker(const char *line);

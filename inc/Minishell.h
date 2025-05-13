/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:27:20 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/12 17:51:19 by mavissar         ###   ########.fr       */
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

typedef struct s_command{
    char    **args;// commands and arguments
    char    *infile;// <
    char    *outfile;// > and >>
    int     append;// 1 for >>, 0 for >
    struct  s_command *next;//next command in pipeline
} t_command;

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
char    *ft_strndup(char *line, int start, int end);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);

/*quotes*/
int quotes_checker(const char *line);

/*lexer utils*/
void    handle_word(const char *line, int *i, t_token **list);
void    handle_operator(const char *line, int *i, t_token **list);
void    handle_quote(const char *line, int *i, t_token **list);

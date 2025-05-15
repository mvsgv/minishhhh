/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:27:20 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/14 14:41:36 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


#include "../Libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"


/*utils*/
char    *ft_strndup(char *line, int start, int end);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

#endif
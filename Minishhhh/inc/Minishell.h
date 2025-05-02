/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:27:20 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/02 17:00:08 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


/*parser*/
char    **split_pipes(char *line);

/*utils*/
char    *ft_strndup(char *line, int start, int end);

/*quotes*/
int quotes_checker(char *line);

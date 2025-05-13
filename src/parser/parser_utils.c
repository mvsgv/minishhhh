/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:22:50 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/12 18:15:11 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minishell.h"

static  t_command   *init_command(void)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->next = NULl;
    return (cmd);
}

static void add_ard(char ***args, char *word)
{
    int i;
    int len;
    char    **new_args;

    i = -1;
    len = 0;
    if (*args)
        while ((*args)[len])
            len++;
    new_args = malloc(sizeof(char *) * (len + 2));
    if (!new_args)
        return ;
    while (++i < len)
        new_args = (*args)[i];
    new_args[len] = ft_strdup(word);
    new_args[len + 1] = NULL;
    free(*args);
    *args = new_args;
}


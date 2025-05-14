/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:52:19 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/14 14:07:34 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_command   *init_command(void)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->next = NULL;
    return (cmd);
}

t_command *parser(t_token *token)
{
    t_token   *tmp;
    t_command   *current;
    t_command   *list;

    list = NULL;
    current = init_command();
    tmp =  token;
    while(tmp)
    {
        if (tmp->type == WORD)
            add_arg(&current->args, tmp->value);
        else if (tmp->type == RED_IN)
        {
            tmp = tmp->next;
            if (!tmp || tmp->type != WORD)
                return (parse_error(list, current, "expected file after '<'"));
            current->infile = ft_strdup(tmp->value);
        }
        else if (tmp->type == RED_OUT || tmp->type == APPEND)
        {
            current->append = (tmp->type == APPEND);
            tmp = tmp->next;
            if (!tmp || tmp->next != WORD)
                return (parse_error(list, current, "expected file after redirection"));
            current->outfile = ft_strdup(tmp->value);
        }
        else if (tmp->type == PIPE)
        {
            add_cmd(&list, current);
            current = init_command();
        }
        tmp = tmp->next;
    }
    add_cmd(&list, current);
    return (list);
}
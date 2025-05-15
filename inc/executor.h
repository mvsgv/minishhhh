/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:19:47 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/15 11:19:48 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "Minishell.h"

typedef struct s_command t_command; 

int is_builtin(t_command *cmd);
int execute_builtin(t_command *cmd);
int handle_infile(t_command *cmd);
int handle_outfile(t_command *cmd);
void execute_command(t_command *cmd);
void execute_all_commands(t_command *cmds);



#endif
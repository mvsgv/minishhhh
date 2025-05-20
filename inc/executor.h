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
typedef struct s_env t_env;

int is_builtin(t_command *cmd);
int execute_builtin(t_command *cmd, t_env *env);
void execute_command(t_command *cmd, t_env *env);
int handle_infile(t_command *cmd);
int handle_outfile(t_command *cmd);
void execute_all_commands(t_command *cmds, t_env *env);
void execute_pipeline(t_command *cmds, t_env *env);
void sigint_handler(int sig);
void setup_signals(void);



#endif
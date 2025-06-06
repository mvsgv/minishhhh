/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:19:20 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 21:27:54 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "Minishell.h"
# include <stdbool.h>

typedef struct s_token	t_token;

typedef struct s_command
{
	char				**args;// commands and arguments
	char				*infile;// <
	char				*outfile;// > and >>
	int					append; // 1 for >>, 0 for >
	struct s_command	*next; // next command in pipeline
}						t_command;

t_command	*parser(t_token *token);
/*utils*/
t_command	*init_command(void);
void		add_arg(char ***args, char *word);
void		free_cmds(t_command *cmd);
void		add_cmd(t_command **list, t_command *cmd);
t_command	*parse_error(t_command *cmd_lst, t_command *current,
				char *msg);
bool		input_checker(const char *line);

#endif
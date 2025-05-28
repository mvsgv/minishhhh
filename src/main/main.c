/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:34:35 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/27 18:28:04 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"
#include "../../inc/lexer.h"

/*Quelle est la différence entre volatile et constant en C  ?
Const spécifie que le pointeur ne peut pas être modifié après son initialisation;
il est protégé contre toute modification ultérieure. 
Le mot-clé volatile spécifie que la valeur associée au nom suivant peut être 
modifiée par des actions autres que celles de l'application utilisateur*/

static bool	empty(char *line)
{
	int	i;

	i = 0;
    while (line[i])
    {
        if (!ft_isspace(line[i]))
            return false;
        i++;
    }
    return true;
}

int	main(int argc, char **argv, char **envp)
{
    char                *line;
	t_env			    *env;
    t_token *tkn;
    t_command *cmd;
    
    env = env_init(envp);
	while (argv && argc)
	{
        setup_signals();
        line = readline("\001\033[38;2;255;20;147m\002minishell> \001\033[0m\002");
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (empty(line)) 
        {
            free(line);
            continue;
        }
        add_history(line);
        if (!input_checker(line)) 
        {
            free(line);
            continue;
        }
        tkn = lexer(line, env, env->exit_status);
        cmd = parser(tkn);
        if (cmd)
        execute_all_commands(cmd, env);
        free_tok(tkn);
        free_cmds(cmd);
        free(line);
	}
    env_free(env);
}

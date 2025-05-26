/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:34:35 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/26 20:31:54 by mavissar         ###   ########.fr       */
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


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *line;
    t_token *tkn;
    t_command *cmd;
    t_env *env;
    

    env = env_init(envp);
    if (!env) 
    {
        fprintf(stderr, "Failed to initialize environment\n");
        return 1;
    }
    setup_signals();
    while (1)
    {
        // line = readline("\033[38;2;255;20;147mminishell> \033[0m");
        line = readline("\001\033[38;2;255;20;147m\002minishell> \001\033[0m\002");
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (empty(line)) {
            free(line);
            continue;
        }
        add_history(line);
        if (!input_checker(line)) {
            free(line);
            continue;
        }
        tkn = lexer(line);
        expand_word(line, env, 0);
            printf()
        cmd = parser(tkn);
        if (cmd)
            execute_all_commands(cmd, env);
        free_tok(tkn);
        free_cmds(cmd);
        free(line);
    }
    env_free(env);
    return 0;
}

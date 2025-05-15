/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:34:35 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/15 12:57:52 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"

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



// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)envp;
//     (void)argv;
//     char *line;
//     t_command   *cmd;
//     t_token     *tkn;


//     //init structure
//     //trouver env path
//     //gerer les signaux SIGINT SIQUIT CTRL
//     while (1)
//     {
//         line = readline("\033[38;2;255;20;147mminishell> \033[0m"); //affiche le prompt et lit une ligne 
//         if (!line)
//         {
//             printf("exit\n");
//             //en cas d erreur j affiche le message exit comme dans c=bash et je break. 
//             break;
//         }
//         if (empty(line))
//             continue;
//         add_history(line);
//         if (input_checker(line))
//         {
//             tkn = lexer(line);
//             cmd = parser(tkn);
//             t_token *tokens = lexer(line);
//             for (t_token *t = tokens; t; t = t->next)
// 	        printf("TOKEN: [%s] type: %d\n", t->value, t->type);
//             free_tok(tkn);
//             free_cmds(cmd);
//             free(line);
//             continue;
//         }
        
//         printf("%s\n", line);
//         free(line);
//     }
//     return (0);
// }



int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;

    char *line;
    t_token *tkn;
    t_command *cmd;

    // Init structures, env, signals ici si besoin

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
        cmd = parser(tkn);
        // EXÉCUTION DES COMMANDES :
        execute_all_commands(cmd);

        // Libérations
        free_tok(tkn);
        free_cmds(cmd);
        free(line);
    }
    return 0;
}

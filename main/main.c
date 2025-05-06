/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:34:35 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/06 18:53:45 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)envp;
    (void)argv;
    char *line;
    
    while (1)
    {
        line = readline("\033[38;2;255;20;147mminishell$ \033[0m"); //affiche le prompt et lit une ligne 
        if (!line)
        {
            printf("exit\n");
            //en cas d erreur j affiche le message exit comme dans c=bash et je break. 
            break;
        }
        if (input_checker(line) == false)
        {
            lexer(line);
            free(line);
            continue;
        }
        if (*line) // si la ligne est n est pas vide on la sauvegarde dans l historique 
            add_history(line);
        printf("%s\n", line);
        free(line);
    }
    return (0);
}
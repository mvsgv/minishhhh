/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:22:50 by mavissar          #+#    #+#             */
/*   Updated: 2025/04/24 18:28:01 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minishell.h"

int quotes_checker(char *line)
{
    int single_qt;
    int double_qt;

    single_qt = 0;
    double_qt = 0;
    while(*line++)
    {
        if (*line == '\'')
            single_qt++;
        if (*line == "\"")
            double_qt++;
    }
    return (single_qt % 2 == 0 && double_qt % 2 == 0); // true or false
}
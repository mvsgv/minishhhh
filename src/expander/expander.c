/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:54:49 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/27 22:01:44 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

/*Handles the case $?
Converts the int into a string, joins it, frees the old strings
Before:
exit_code = 127
result    = "Command failed with code: "
After:
val = ft_itoa(exit_code); --> converts 127 to "127" --> val = "127"
tmp = ft_strjoin(result, val);
Concatenates "Command failed with code: " + "127"
tmp = "Command failed with code: 127"
*/
static char    *exit_code_expand(int *i, int exit_cd, char *res)
{
    char    *val;
    char    *tmp;
    
    (*i)++;//on avance du ? au prochain element
    val = ft_itoa(exit_cd);
    tmp = ft_strjoin(res, val);
    free(val);
    free(res);
    return (tmp);
}
/*
str → the input line (e.g. "echo $USER")
i → pointer to the current index in the string
env → your environment list (t_env)
res → the result string built so far (e.g., "echo ")
Let’s say:

    str = "echo $USER"

    *i = 5 (points to the U after $)

    env contains USER=mavissar

    res = "echo " (space included)
*/

static char *env_var_expansion(const char *str, int *i, t_env *env)
{
    char *key;
    char *val;
    char *tmp;
    int start;

    (*i)++;
    start = *i;

    // Extract the variable name
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;

    key = ft_substr(str, start, *i - start); // Extract the variable name
    if (!key)
        return (NULL);

    printf("Key: %s\n", key);

    val = get_env_value(key, env); // Get the value of the variable

    tmp = ft_strdup(val); // Duplicate the value (do not include anything before the variable)
    free(key);

    if (!tmp)
        return (NULL); // If duplication fails, return NULL

    printf("Expanded variable: %s\n", tmp);
    return (tmp);
}

/*Its job is to add one character (the current str[i]) to a growing result string res.
char tmp[2] = {str[i], 0};
str[i] = 'c'     →    tmp = ['c', '\0']     →    tmp = "c"
comme je itere i dans ma fonction principale, mon caractere change et le prochain
se rajoute
Is used when there’s no special $ expansion needed
Is memory-safe (free(res))
Ensures quote handling or $ logic doesn’t interfere
*/
static char    *append_char_to_res(char *res, char c)
{
    char    tmp[2];
    char    *join;
    
    tmp[0] = c;
    tmp[1] = '\0';
    join = ft_strjoin(res, tmp);
    free(res);
    res = join;
    return (res);
}

static void    dq_sq(char c, int *in_sq, int *in_dq)
{
    
    if (c == '\'' && !(*in_dq))
        *in_sq = !(*in_sq);
    else if (c == '\"' && !(*in_sq))
        *in_dq = !(*in_dq);
}

char *expand_word(const char *str, t_env *env, int exit_cd)
{
    int i;
    int in_sq;
    int in_dq;
    char *res;

    i = 0;
    in_dq = 0;
    in_sq = 0;
    res = ft_calloc(1, 1); /* equivalent to strdup("") */
    if (!res)
        return (NULL);

    while (str[i])
    {
        dq_sq(str[i], &in_sq, &in_dq);
        if (str[i] == '$' && !in_sq)
        {
            if (str[i + 1] == '?')
            {
                res = exit_code_expand(&i, exit_cd, res);
                if (!res)
                    return (NULL);
            }
            else
            {
                char *tmp = env_var_expansion(str, &i, env);
                if (!tmp)
                {
                    free(res);
                    return (NULL);
                }
                char *new_res = ft_strjoin(res, tmp); // Append expanded variable to result
                free(res);
                free(tmp);
                res = new_res;
                if (!res)
                    return (NULL);
            }
        }
        else
        {
            res = append_char_to_res(res, str[i]);
            if (!res)
                return (NULL);
            i++;
        }
    }
    return (res);
}

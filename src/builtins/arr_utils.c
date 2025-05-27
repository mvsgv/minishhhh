#include "../../inc/builtins.h"

char **ft_arrdup(char **arr)
{
    int i;
    int len;
    char **dup;
    
    i = 0;
    len = 0;
    while (arr[len])
        len++;
    dup = malloc(sizeof(char *) * (len + 1));
    if (!dup)
        return (NULL);
    while (i < len) 
    {
        dup[i] = ft_strdup(arr[i]);
        if (!dup[i]) 
        {
            while (--i >= 0)
                free(dup[i]);
            free(dup);
            return (NULL);
        }
        i++;
    }
    dup[len] = NULL;
    return (dup);
}

void ft_free_arr(char **arr)
{
    int i;
    
    i = 0;
    if (!arr)
        return;
    
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void ft_sort_strarr(char **arr)
{
    int i;
    int j;
    char *temp;
    int len;
    
    len = 0;
    while (arr[len])
        len++;
    for (i = 0; i < len - 1; i++) 
    {
        for (j = 0; j < len - i - 1; j++) 
        {
            if (ft_strcmp(arr[j], arr[j + 1]) > 0) 
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:00:27 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/26 20:01:08 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}

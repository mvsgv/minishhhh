/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:08:15 by mavissar          #+#    #+#             */
/*   Updated: 2025/05/06 18:54:12 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	if (dst == src)
		return (dst);
	while (i < n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (dst);
}
/*int	main()
{
	unsigned char src[] = "two";
	unsigned char dst[20] = "one";
	
	printf("%s" , ft_memcpy(dst, src, 1));
}*/
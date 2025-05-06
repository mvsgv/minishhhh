/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:36:55 by mavissar          #+#    #+#             */
/*   Updated: 2024/05/07 18:21:44 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_lenght;
	size_t	src_lenght;

	i = 0;
	if (!dst && dstsize == 0)
		return (0);
	dst_lenght = ft_strlen(dst);
	src_lenght = ft_strlen(src);
	if (dstsize == 0 || dstsize <= dst_lenght)
		return (dstsize + src_lenght);
	while (src[i] && dst_lenght + i < dstsize - 1)
	{
		dst[dst_lenght + i] = src[i];
		i++;
	}
	dst[dst_lenght + i] = '\0';
	return (dst_lenght + src_lenght);
}
/*int	main()
{
	char	dst[] = "colision";
	const char src[] = "vision";

	printf("%zu", ft_strlcat(dst, src, 4));
}*/
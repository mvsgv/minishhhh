/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:33:40 by mavissar          #+#    #+#             */
/*   Updated: 2025/06/04 17:00:26 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_quantity(int n)
{
	size_t	qtt_of_num;

	qtt_of_num = 0;
	if (n <= 0)
		qtt_of_num = 1;
	while (n)
	{
		n /= 10;
		++qtt_of_num;
	}
	return (qtt_of_num);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = get_quantity(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[--len] = '8';
			n /= 10;
		}
		n = -n;
	}
	while (len-- && n)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

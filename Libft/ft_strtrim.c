/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:29:58 by mavissar          #+#    #+#             */
/*   Updated: 2024/05/07 18:23:04 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (start == end)
		return (ft_strdup(""));
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, start, end - start));
}
// int	main()
// {
// 	printf("%s\n", ft_strtrim("TRalalalalalTRlATRTR","TR"));
// 	printf("%s\n", ft_strtrim("hello44you", "4"));
// 	printf("%s\n", ft_strtrim("44hello44y", ""));
// 	printf("%s\n", ft_strtrim("", "4"));
// 	printf("%s\n", ft_strtrim("444hello44y", "4444"));
// }
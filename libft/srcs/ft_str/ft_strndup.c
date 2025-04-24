/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:23:03 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/22 18:25:09 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *source, size_t n)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(source);
	if (len > n)
		len = n;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	while (source[i] && i < n)
	{
		str[i] = source[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

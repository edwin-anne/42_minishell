/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:03:16 by eanne             #+#    #+#             */
/*   Updated: 2025/03/11 10:46:19 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdprintf.h"

int	processing_number(int fd, int letter, va_list args)
{
	char	*str;
	int		len;

	if (letter == 'd' || letter == 'i')
	{
		str = ft_itoa(va_arg(args, int));
		if (!str)
			return (-1);
		len = ft_strlen(str);
		ft_putstr_fd(str, fd);
		free(str);
		return (len);
	}
	else if (letter == 'u')
	{
		str = ft_uitoa(va_arg(args, unsigned int));
		if (!str)
			return (-1);
		len = ft_strlen(str);
		ft_putstr_fd(str, fd);
		free(str);
		return (len);
	}
	return (-1);
}

char	*ft_uitoa(unsigned int num)
{
	char	buffer[11];
	int		i;

	i = 10;
	buffer[i--] = '\0';
	if (num == 0)
		buffer[i--] = '0';
	while (num > 0)
	{
		buffer[i--] = '0' + (num % 10);
		num /= 10;
	}
	return (ft_strdup(&buffer[i + 1]));
}

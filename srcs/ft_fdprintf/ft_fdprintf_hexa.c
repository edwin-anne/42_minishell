/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf_hexa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:19:38 by eanne             #+#    #+#             */
/*   Updated: 2025/03/11 11:27:38 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdprintf.h"

int	processing_hexa(int fd, int letter, va_list args)
{
	char	buffer[17];
	int		len;
	int		i;

	if (letter == 'p')
		return (processing_void_pointer(fd, va_arg(args, void *)));
	else if (letter == 'x')
	{
		len = base16_converter(va_arg(args, unsigned int), buffer);
		write(fd, buffer + (16 - len), len);
		return (len);
	}
	else if (letter == 'X')
	{
		len = base16_converter(va_arg(args, unsigned int), buffer);
		i = 16 - len;
		while (i < 16)
		{
			buffer[i] = ft_toupper(buffer[i]);
			i++;
		}
		write(fd, buffer + (16 - len), len);
		return (len);
	}
	return (-1);
}

int	base16_converter(uintptr_t num, char *buffer)
{
	char	hex_digits[17];
	int		i;
	int		len ;

	ft_strlcpy(hex_digits, "0123456789abcdef", 17);
	i = 15;
	len = 0;
	ft_memset(buffer, '\0', 17);
	if (num == 0)
	{
		buffer[i] = '0';
		return (1);
	}
	while (num > 0)
	{
		buffer[i--] = hex_digits[num % 16];
		num /= 16;
		len++;
	}
	return (len);
}

int	processing_void_pointer(int fd, void *ptr)
{
	uintptr_t	address;
	int			len;
	char		buffer[17];

	if (!ptr)
		return (write_nil(fd));
	address = (uintptr_t)ptr;
	len = base16_converter(address, buffer);
	write(fd, "0x", 2);
	write(fd, buffer + (16 - len), len);
	return (len + 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:18:39 by eanne             #+#    #+#             */
/*   Updated: 2025/03/11 12:05:32 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdprintf.h"

int	ft_fdprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			count += processing(fd, *format, args);
		}
		else
		{
			write(fd, format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}

int	parsing_format(int fd, const char **format)
{
	if (**format == '%')
		return (*(*format)++);
	else
	{
		write(fd, *format, 1);
		return (0);
	}
	(*format)++;
}

int	processing_letter(int fd, int letter, va_list args)
{
	char	*str;
	int		value;

	if (letter == 'c')
	{
		value = va_arg(args, int);
		write(fd, &value, 1);
		return (1);
	}
	else if (letter == 's')
	{
		str = va_arg(args, char *);
		if (str == NULL)
			return (write_null(fd));
		ft_putstr_fd(str, fd);
		return (ft_strlen(str));
	}
	return (-1);
}

int	processing(int fd, int format, void *args)
{
	int	result_letter;
	int	result_number;
	int	result_hexa;

	result_letter = processing_letter(fd, format, args);
	result_number = processing_number(fd, format, args);
	result_hexa = processing_hexa(fd, format, args);
	if (result_letter != -1)
		return (result_letter);
	else if (result_number != -1)
		return (result_number);
	else if (result_hexa != -1)
		return (result_hexa);
	else
		return (write_format(fd, format));
}

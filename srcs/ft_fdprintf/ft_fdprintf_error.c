/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:57:10 by eanne             #+#    #+#             */
/*   Updated: 2025/03/11 10:47:30 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdprintf.h"

int	write_null(int fd)
{
	write(fd, "(null)", 6);
	return (6);
}

int	write_nil(int fd)
{
	write(fd, "(nil)", 5);
	return (5);
}

int	write_format(int fd, int letter)
{
	write(fd, "%", 1);
	if (letter == '%')
		return (1);
	write(fd, &letter, 1);
	return (2);
}

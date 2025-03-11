/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:58:52 by eanne             #+#    #+#             */
/*   Updated: 2025/03/11 12:05:33 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDPRINTF_H
# define FT_FDPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

# include "libft.h"

int	ft_fdprintf(int fd, const char *format, ...);
int	parsing_format(int fd, const char **format);
int	processing_letter(int fd, int letter, va_list args);
int	processing(int fd, int format, void *args);

/*######	HEXA   	######*/
int	processing_hexa(int fd, int letter, va_list args);
int	base16_converter(uintptr_t num, char *buffer);
int	processing_void_pointer(int fd, void *ptr);

/*######	NUMBER   	######*/
int	processing_number(int fd, int letter, va_list args);
char	*ft_uitoa(unsigned int num);

/*######	ERROR   	######*/
int	write_null(int fd);
int	write_nil(int fd);
int	write_format(int fd, int letter);

#endif
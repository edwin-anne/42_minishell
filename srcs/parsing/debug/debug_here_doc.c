/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:10:08 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/03/02 12:12:40 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	debug_here_doc(char *filepath, char *limiter)
{
	printf("\n========= Debug Here Doc =========\n\n");
	printf("Nom du fichier : %s\n", filepath);
	printf("Limiteur : %s\n", limiter);
}
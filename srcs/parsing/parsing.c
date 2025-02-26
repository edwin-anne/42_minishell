/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:41:49 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/26 22:00:39 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing(char *line, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	printf("Ceci est un minishell qui marche en voici la preuve je peux réecrire ce que tu as marqué -> %s", line);
}
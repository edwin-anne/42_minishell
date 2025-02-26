/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:42:03 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/26 21:57:42 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

/*######	PARSING 	######*/
void	parsing(char *line, int argc, char **argv, char **envp);

#endif
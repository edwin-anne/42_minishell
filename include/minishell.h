/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:57:53 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/26 20:37:28 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>

typedef struct t_minishell
{
	char	*infile;
	int		in_fd;
	char	*outfile;
	int		out_fd;
	char	**cmd;
	int		count_cmd;
	pid_t	*pids;
	char	**path;
	bool	here_doc;
}	t_minishell;


#endif
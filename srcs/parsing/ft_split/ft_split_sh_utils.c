/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sh_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:25:51 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 18:30:29 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_update_quotes(const char *str, int *i, int *sq, int *dq)
{
	if (str[*i] == '\'' && !(*dq))
		*sq = !(*sq);
	else if (str[*i] == '"' && !(*sq))
		*dq = !(*dq);
}

void	ft_skip_sep(const char *str, int *i, char c)
{
	while (str[*i] == c && str[*i])
		(*i)++;
}

static void	ft_skip_word(const char *str, int *i, char c)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (str[*i] && (str[*i] != c || sq || dq))
	{
		ft_update_quotes(str, i, &sq, &dq);
		(*i)++;
	}
}

int	ft_countnbr(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		ft_skip_sep(str, &i, c);
		if (str[i])
		{
			words++;
			ft_skip_word(str, &i, c);
		}
	}
	return (words);
}

void	ft_freetab(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:24:58 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/28 18:32:53 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_update_quotes(const char *s, int *i, int *sq, int *dq)
{
	if (s[*i] == '\'' && !(*dq))
		*sq = !(*sq);
	else if (s[*i] == '"' && !(*sq))
		*dq = !(*dq);
}

static int	ft_get_word_len(const char *s, int *i, char c)
{
	int	start;
	int	sq;
	int	dq;

	start = *i;
	sq = 0;
	dq = 0;
	while (s[*i] && (s[*i] != c || sq || dq))
	{
		ft_update_quotes(s, i, &sq, &dq);
		(*i)++;
	}
	return (*i - start);
}

static char	**ft_cpystr(char **tab, const char *s, char c, int nb)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i] && j < nb)
	{
		ft_skip_sep(s, &i, c);
		if (s[i])
		{
			len = ft_get_word_len(s, &i, c);
			tab[j] = ft_substr(s, i - len, len);
			if (!tab[j])
				return (ft_freetab(tab, j), NULL);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_sh(const char *s, char c)
{
	char	**tab;
	int		nb;

	if (!s)
		return (NULL);
	nb = ft_countnbr(s, c);
	tab = malloc(sizeof(char *) * (nb + 1));
	if (!tab)
		return (NULL);
	return (ft_cpystr(tab, s, c, nb));
}

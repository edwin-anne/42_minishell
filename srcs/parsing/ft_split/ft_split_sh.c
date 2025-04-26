/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:24:58 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/04/25 10:26:21 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countnbr(const char *str, char c)
{
	int	words;
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	words = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (!in_squote && !in_dquote)
		{
			while (str[i] == c && !in_squote && !in_dquote)
				i++;
			if (str[i] != '\0' && str[i] != c)
			{
				words++;
				while (str[i] && (str[i] != c || in_squote || in_dquote))
				{
					if (str[i] == '\'' && !in_dquote)
						in_squote = !in_squote;
					else if (str[i] == '"' && !in_squote)
						in_dquote = !in_dquote;
					i++;
				}
				continue ;
			}
		}
		if (str[i])
			i++;
	}
	return (words);
}

static void	ft_freetab(char **str, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free (str[i]);
		i++;
	}
	free (str);
}

static char	**ft_cpystr(char **str, char const *s, char c, int nbwords)
{
	int	start;
	int	i;
	int	j;
	int	in_squote;
	int	in_dquote;

	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (s[i] && j < nbwords)
	{
		while (s[i] && s[i] == c && !in_squote && !in_dquote)
			i++;
		start = i;
		while (s[i] && (s[i] != c || in_squote || in_dquote))
		{
			if (s[i] == '\'' && !in_dquote)
				in_squote = !in_squote;
			else if (s[i] == '"' && !in_squote)
				in_dquote = !in_dquote;
			i++;
		}
		if (i > start)
		{
			str[j] = ft_substr(s, start, i - start);
			if (!str[j])
				return (ft_freetab(str, j), NULL);
			j++;
		}
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split_sh(char const *s, char c)
{
	int		nbrwords;
	char	**str;

	if (!s)
		return (NULL);
	nbrwords = ft_countnbr(s, c);
	str = malloc((nbrwords + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (ft_cpystr(str, s, c, nbrwords));
}

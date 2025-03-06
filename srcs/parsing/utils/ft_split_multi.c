/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:20:42 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/28 18:44:14 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int is_delimiter(char c, char **delimiters)
{
    int i = 0, j = 0;

    while (delimiters[i])
    {
        j = 0;
        while (delimiters[i][j])
        {
            if (c == delimiters[i][j])
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

static int count_words(const char *str, char **delimiters)
{
    int words = 0;
    int i = 0;

    while (str[i])
    {
        while (str[i] && is_delimiter(str[i], delimiters))
            i++;
        if (str[i])
        {
            words++;
            while (str[i] && !is_delimiter(str[i], delimiters))
                i++;
        }
    }
    return (words);
}

static void free_split(char **split, int nb)
{
    int i = 0;
    while (i < nb)
    {
        free(split[i]);
        i++;
    }
    free(split);
}

static char **fill_split(char **split, const char *s, char **delimiters, int word_count)
{
    int i = 0, j = 0, start = 0;

    while (s[i] && j < word_count)
    {
        while (s[i] && is_delimiter(s[i], delimiters))
            i++;
        start = i;
        while (s[i] && !is_delimiter(s[i], delimiters))
            i++;
        if (i > start)
        {
            split[j] = ft_substr(s, start, i - start);
            if (!split[j])
                return (free_split(split, j), NULL);
            j++;
        }
    }
    split[j] = NULL;
    return (split);
}

char **ft_split_multi(const char *s, char **delimiters)
{
    char **split;
    int word_count;

    if (!s || !delimiters)
        return (NULL);
    word_count = count_words(s, delimiters);
    split = (char **)malloc(sizeof(char *) * (word_count + 1));
    if (!split)
        return (NULL);
    return (fill_split(split, s, delimiters, word_count));
}

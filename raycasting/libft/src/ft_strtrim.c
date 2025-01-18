/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:05:43 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/18 06:45:37 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_chartrim(char c, const char *set)
{
	int	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_countlens(const char *s1, const char *set)
{
	int	i;
	int	tot_char_trim;

	i = 0;
	tot_char_trim = 0;
	while (ft_chartrim(s1[i], set) && s1[i])
	{
		tot_char_trim++;
		i++;
	}
	if (s1[i])
	{
		i = ft_strlen(s1) - 1;
		while (ft_chartrim(s1[i], set))
		{
			tot_char_trim++;
			i--;
		}
	}
	return (ft_strlen(s1) - tot_char_trim);
}

char	*ft_strtrim(char *s1, char const *set)
{
	int		i;
	int		tot_len;
	char	*rep;
	int		j;

	if (!s1)
		return (NULL);
	tot_len = ft_countlens(s1, set) + 1;
	rep = ft_calloc(tot_len, sizeof(char));
	if (!rep)
		return (NULL);
	i = 0;
	j = 0;
	while (ft_chartrim(s1[i], set))
		i++;
	while (j < tot_len - 1)
	{
		rep[j] = s1[i];
		j++;
		i++;
	}
	free(s1);
	return (rep);
}

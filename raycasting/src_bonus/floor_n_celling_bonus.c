/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_n_celling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:45:26 by armitite          #+#    #+#             */
/*   Updated: 2025/01/29 17:45:14 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

char	*add_to_string(char c, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (ft_strlen(str) == 0)
	{
		str = malloc(sizeof(char) * 2);
		str[i] = c;
		str[i + 1] = '\0';
	}
	else
	{
		tmp = malloc(sizeof(char) * (ft_strlen(str) + 2));
		while (str[i])
		{
			tmp[i] = str[i];
			i++;
		}
		tmp[i] = c;
		tmp[i + 1] = '\0';
		free(str);
		str = tmp;
	}
	return (str);
}

char	*nbr_hexa(int nbr, char *str)
{
	int		len;
	char	*base;

	base = "0123456789ABCDEF";
	len = 16;
	if (len > nbr)
	{
		str = add_to_string(base[nbr], str);
	}
	else
	{
		str = nbr_hexa((nbr / len), str);
		str = add_to_string(base[nbr % len], str);
	}
	return (str);
}

char	*get_floor(t_game *game)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	tmp = str;
	str = nbr_hexa(game->sprt.floor[0], str);
	free(tmp);
	str = nbr_hexa(game->sprt.floor[1], str);
	str = nbr_hexa(game->sprt.floor[2], str);
	return (str);
}

char	*get_ceiling(t_game *game)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	tmp = str;
	str = nbr_hexa(game->sprt.ceiling[0], str);
	free(tmp);
	str = nbr_hexa(game->sprt.ceiling[1], str);
	str = nbr_hexa(game->sprt.ceiling[2], str);
	return (str);
}

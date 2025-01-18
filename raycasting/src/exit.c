/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:06:44 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/18 17:02:45 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	ft_freewall(char **wall)
{
	int	i;

	i = -1;
	if (!wall)
		return ;
	while (++i < 64 && wall[i])
		free(wall[i]);
	if (wall)
		free(wall);
}

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	ft_freeparse(t_game *game)
{
	free(game->sprt.floor);
	free(game->sprt.ceiling);
	free(game->sprt.north);
	free(game->sprt.west);
	free(game->sprt.east);
	free(game->sprt.south);
	free(game->mlx);
}

void	ft_freemap(char **map, t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.lin)
		free(map[i]);
	free(map);
}

void	ft_free(char **rep)
{
	int	i;

	i = 0;
	while (rep[i] != NULL)
	{
		free(rep[i]);
		i++;
	}
	free(rep);
}

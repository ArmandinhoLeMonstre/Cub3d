/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 01:59:41 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/29 18:51:15 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_filetype(char *file)
{
	if ((file[ft_strlen(file) - 1] == 'b') && (file[ft_strlen(file) - 2] == 'u')
		&& (file[ft_strlen(file) - 3] == 'c')
		&& (file[ft_strlen(file) - 4] == '.'))
		return (1);
	else
		ft_error("Error\nWrong type of file\n");
	return (0);
}

void	ft_init_ptr(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Error\nFail to connect to server\n");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
		ft_error("Error\nFail to connect to server\n");
}

int	main(int ac, char **av)
{
	t_game	game;
	char	*floor;
	char	*ceiling;

	if (ac == 2)
	{
		check_filetype(av[1]);
		game.file = av[1];
		parsing(av[1], &game);
		floor = get_floor(&game);
		ceiling = get_ceiling(&game);
		game.floor = ft_atoi_base(floor, "0123456789ABCDEF");
		game.ceiling = ft_atoi_base(ceiling, "0123456789ABCDEF");
		free(floor);
		free(ceiling);
		if (ft_create_map(ft_open(av[1]), &game)
			|| ft_findpalyer(game.map.map, &game, -1))
		{
			ft_freeparse(&game);
			ft_error("Error\nInvalid Map\n");
		}
		ft_game(&game);
	}
}

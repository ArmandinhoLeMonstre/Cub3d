/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:43:58 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/13 01:18:33 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void ft_freeall(t_game *game)
{
	free(game->sprites.floor);
	free(game->sprites.ceiling);
	mlx_destroy_image(game->mlx.mlx, game->sprites.north);
	mlx_destroy_image(game->mlx.mlx, game->sprites.west);
	mlx_destroy_image(game->mlx.mlx, game->sprites.east);
	mlx_destroy_image(game->mlx.mlx, game->sprites.south);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
}

long	ft_atorgb(char *str)
{
	int		i;
	long	num;
	int		len;

	i = -1;
	while (ft_isspace(str[++i]))
		;
	if (!ft_isdigit(str[i]) && str[i] != '+')
		ft_error("Error\nInvalid RBG value\n");
	num = 0;
	len = 0;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		++len;
		num = (num * 10) + (str[i++] - '0');
	}
	// if (str[i] != 0)
	// 	ft_error("Error\nInvalid RBG value\n");
	if (num > 255 || len > 10)
		ft_error("Error\nInvalid RBG value\n");
	return (num);
}

int	ft_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nFailed to open file\n");
	return (fd);
}

void	ft_setid(char *str, int len, t_game *game, int id)
{
	int		i;
	int		img_width;
	int		img_height;
	char	*dup;
	void	*ptr;

	i = -1;
	while (str[++i + len] && ft_isspace(str[i + len]))
		;
	if (str[i + len])
		ft_error("Error\nInvalid identifier\n");
	dup = ft_strdup(str);
	dup[len] = 0;
	ptr = mlx_xpm_file_to_image(game->mlx.mlx, dup, &img_width, &img_height);
	free(dup);
	if (!ptr)
		ft_error("Error\nFail xpm to img\n");
	if (id == 0)
		game->sprites.north = ptr;
	else if (id == 1)
		game->sprites.south = ptr;
	else if (id == 2)
		game->sprites.east = ptr;
	else if (id == 3)
		game->sprites.west = ptr;
}

void	ft_checkrgb(char *str, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (!ft_isdigit(str[i]))
			ft_error("Error\nInvalid identifier\n");
		while (ft_isdigit(str[i]))
			i++;
		if (str[i++] != ',' || !ft_isdigit(str[i]))
			ft_error("Error\nInvalid identifier\n");
		while (ft_isdigit(str[i]))
			i++;
		if (str[i++] != ',' || !ft_isdigit(str[i]))
			ft_error("Error\nInvalid identifierdd\n");
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] && !ft_isspace(str[i]))
			ft_error("Error\nInvalid identifier\n");
	}
	i = -1;
	while (str[++i + len] && ft_isspace(str[i + len]))
		;
	if (str[i + len])
		ft_error("Error\nInvalid identifier\n");
}

void	ft_setcolor(char *str, int len, t_game *game, int id)
{
	int	i;
	int	*rgb;

	ft_checkrgb(str, len);
	rgb = malloc (sizeof(int) * 3);
	if (!rgb)
		ft_error("Error\nMalloc");
	i = -1;
	if (++i < len)
	{
		rgb[0] = (int) ft_atorgb(&str[i]);
		while (ft_isdigit(str[i]))
			i++;
		rgb[1] = (int) ft_atorgb(&str[++i]);
		while (ft_isdigit(str[i]))
			i++;
		rgb[2] = (int) ft_atorgb(&str[++i]);
		while (ft_isdigit(str[i]))
			i++;
	}
	if (id == 4)
		game->sprites.floor = rgb;
	else if (id == 5)
		game->sprites.ceiling = rgb;
}

void	ft_getidentifier(char *str, t_game *game, int id)
{
	int		i;
	int		len;

	i = -1;
	if (str[++i])
	{
		while (ft_isspace(str[++i]))
			;
		if (str[i])
		{
			len = -1;
			while (str[i + (++len)] && !ft_isspace(str[i + len]))
				;
			if (id <= 3)
				ft_setid(&str[i], len, game, id);
			else
				ft_setcolor(&str[i], len, game, id);
		}
	}
}

void	ft_getinfo(char *str, t_game *game)
{
	int	i;

	i = -1;
	while (ft_isspace(str[++i]))
		;
	printf("str : %s\n", str);
	if (str[i] && str[i + 1])
	{
		if (str[i] == 'N' && str[i + 1] == 'O' && !game->sprites.north)
			ft_getidentifier(&str[i + 2], game, 0);
		else if (str[i] == 'S' && str[i + 1] == 'O' && !game->sprites.south)
			ft_getidentifier(&str[i + 2], game, 1);
		else if (str[i] == 'E' && str[i + 1] == 'A' && !game->sprites.east)
			ft_getidentifier(&str[i + 2], game, 2);
		else if (str[i] == 'W' && str[i + 1] == 'E' && !game->sprites.west)
			ft_getidentifier(&str[i + 2], game, 3);
		else if (str[i] == 'F' && !game->sprites.floor)
			ft_getidentifier(&str[i + 1], game, 4);
		else if (str[i] == 'C' && !game->sprites.ceiling)
			ft_getidentifier(&str[i + 1], game, 5);
		else
			ft_error("Error\nInvalid identifierff\n");
	}
}

void	ft_init_ptr(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
	{
		ft_putstr_fd("Error\nFail to connect to server\n", 2);
		exit(EXIT_FAILURE);
	}
	game->mlx.win = mlx_new_window(game->mlx.mlx, 400, 400,
			"so_long");
}
void	gameloop(t_game *game)
{
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->sprites.north, 0, 0);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->sprites.south, 64, 0);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->sprites.east, 64 * 2, 0);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->sprites.west, 64 * 3, 0);
	mlx_loop(game->mlx.mlx);
}

void ft_init_pars(t_game *game)
{
	game->sprites.floor = NULL;
	game->sprites.ceiling = NULL;
	game->sprites.north = NULL;
	game->sprites.south = NULL;
	game->sprites.east = NULL;
	game->sprites.west = NULL;
	game->mdata.bool_id = 0;
	game->mdata.s_line = 1;
	game->mdata.col = 0;
	game->mdata.lin = 0;
}

int	ft_emptyline(char **line, t_game *game, int fd)
{
	int		i;
	char	*str;

	str = *line;
	while (str)
	{
		i = -1;
		while (str[++i] && ft_isspace(str[i]))
			;
		if (str[i] != 0)
		{
			if (str[i] != '1')
				return (free(str), 1);
			break ;
		}
		free(str);
		game->mdata.s_line++;
		str = get_next_line(fd);
	}
	*line = str;
	return (0);
}

int ft_checkeof(char *str, int fd)
{
	int	i;

	i = -1;
	while (str)
	{
		i = -1;
		while (str[++i] && ft_isspace(str[i]))
			;
		if (str[i] != 0)
			return (free(str), 1);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	ft_mapchar(t_game *game, char *str, int fd)
{
	int	i;

	i = -1;
	while (str)
	{
		i = -1;
		while (str[++i] && ft_isspace(str[i]))
			;
		if (str[i] == 0)
			break ;
		i = -1;
		while (str[++i] && (ft_isspace(str[i]) || str[i] == '0' || str[i] == '1'
				|| str[i] == 'N' || str[i] == 'S'
				|| str[i] == 'W' || str[i] == 'E'))
				;
		if (str[i] && str[i] != '\n')
			return (free(str), 1);
		game->mdata.lin++;
		if ((int) ft_strlen(str) > game->mdata.col)
			game->mdata.col = ft_strlen(str);
		free(str);
		str = get_next_line(fd);
	}
	return (ft_checkeof(str, fd));
}

int ft_create_map(int fd, t_game *game)
{
	char	*str;
	int		i;

	i = -1;
	str = get_next_line(fd);
	while (++i < game->mdata.s_line - 1)
	{
		free(str);
		str = get_next_line(fd);
	}
	game->mdata.map = malloc(sizeof(char *) * game->mdata.lin);
	if (!game->mdata.map)
		return (ft_freeall(game), 1);
	i = -1;
	while (++i < game->mdata.lin)
	{
		game->mdata.map[i] = calloc(sizeof(char), game->mdata.col + 1);
		if (!game->mdata.map[i])
			return (free(game->mdata.map), ft_freeall(game), 1);
		ft_strlcpy(game->mdata.map[i], str, ft_strlen(str) + 1);
		free(str);
		str = get_next_line(fd);
	}
	return (close(fd), free(str), 0);
}

int	ft_backtrack(int x, int y, t_game * game, char **plan)
{
	if (plan[y][x] == '1')
		return (0);
	if (x < 0 || x >= game->mdata.col || y < 0 || y >= game->mdata.lin || plan[y][x] == ' ' || plan[y][x] == '\0')
		return (1);
	if (plan[y][x] == '0' || plan[y][x] == 'N' || plan[y][x] == 'S'
			|| plan[y][x] == 'E' || plan[y][x] == 'W')
	{
		plan[y][x] = 'V';
		if (ft_backtrack(x - 1, y, game, plan)
			|| ft_backtrack(x + 1, y, game, plan)
			|| ft_backtrack(x, y + 1, game, plan)
			|| ft_backtrack(x, y - 1, game, plan))
			return (1);
	}
	return (0);
}

int	ft_findo(char **map, t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->mdata.lin)
	{
		x = -1;
		while (++x < game->mdata.col)
		{
			if (map[y][x] == '0')
				return ((y * game->mdata.col) + x);
		}
	}
	return (-1);
}

void	ft_freemap(char **map, t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->mdata.lin)
		free(map[i]);
	free(map);
}

void ft_mapinfo(int fd, t_game *game, char *str)
{
	int	find;

	if (ft_emptyline(&str, game, fd) || ft_mapchar(game, str, fd))
	{
		ft_freeall(game);
		ft_error("Error\nInvalid map\n");
	}
	fd = ft_open(game->file);
	if (ft_create_map(fd, game))
		ft_error("Error\nMalloc\n");
	find = ft_findo(game->mdata.map, game);
	while (find != -1)
	{
		printf("find : %d\n", find);
		if (ft_backtrack(find % game->mdata.col, find / game->mdata.col,
				game, game->mdata.map))
		{
			ft_freemap(game->mdata.map, game);
			ft_freeall(game);
			ft_error("Error\nInvalid map\n");
		}
		find = ft_findo(game->mdata.map, game);
	}
	ft_freemap(game->mdata.map, game);
}

void	parsing(char *file, t_game *game)
{
	int			fd;
	char		*line;
	t_sprites	*sprites;

	fd = ft_open(file);
	ft_init_pars(game);
	line = get_next_line(fd);
	sprites = &game->sprites;
	while (line && !game->mdata.bool_id)
	{
		ft_getinfo(line, game);
		free(line);
		line = get_next_line(fd);
		if (sprites->ceiling && sprites->floor && sprites->north
			&& sprites->south && sprites->east && sprites->west)
			game->mdata.bool_id = 1;
		game->mdata.s_line++;
	}
	ft_mapinfo(fd, game, line);
}

int	check_filetype(char *file)
{
	if ((file[ft_strlen(file) - 1] == 'b') && (file[ft_strlen(file) - 2] == 'u')
		&& (file[ft_strlen(file) - 3] == 'c')
		&& (file[ft_strlen(file) - 4] == '.'))
		return (1);
	else
	{
		ft_putstr_fd("Error\nWrong type of file\n", 2);
		exit(1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2)
	{
		check_filetype(av[1]);
		game.file = av[1];
		ft_init_ptr(&game);
		parsing(av[1], &game);
		// gameloop(&game);
		ft_freeall(&game);
	}
}

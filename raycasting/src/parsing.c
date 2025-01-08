/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:43:58 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/08 21:33:47 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
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
	ptr= mlx_xpm_file_to_image(game->mlx.mlx, dup, &img_width, &img_height);
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
	free(dup);
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
	if (str[i] && str[i + 1])
	{
		if (str[i] == 'N' && str[i + 1] == 'O')
			ft_getidentifier(&str[i + 2], game, 0);
		else if (str[i] == 'S' && str[i + 1] == 'O')
			ft_getidentifier(&str[i + 2], game, 1);
		else if (str[i] == 'E' && str[i + 1] == 'A')
			ft_getidentifier(&str[i + 2], game, 2);
		else if (str[i] == 'W' && str[i + 1] == 'E')
			ft_getidentifier(&str[i + 2], game, 3);
		else if (str[i] == 'F')
			ft_getidentifier(&str[i + 1], game, 4);
		else if (str[i] == 'C')
			ft_getidentifier(&str[i + 1], game, 5);
		else
			ft_error("Error\nInvalid identifier\n");
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
	mlx_loop(game->mlx.mlx);
}

int main(int ac, char **av)
{
	t_game game;

	(void) ac;
	// ft_init_ptr(&game);
	ft_getinfo(av[1], &game);
	// gameloop(&game);
}

// int	parsing(char *file, t_game *game)
// {
// 	int		fd;
// 	char	*line;

// 	fd = ft_open(file);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
		
// 		free(line);
// 	}
// }

// int	check_filetype(char *file)
// {
// 	if ((file[ft_strlen(file) - 1] == 'b') && (file[ft_strlen(file) - 2] == 'u')
// 		&& (file[ft_strlen(file) - 3] == 'c')
// 		&& (file[ft_strlen(file) - 4] == '.'))
// 		return (1);
// 	else
// 	{
// 		ft_putstr_fd("Error\nWrong type of file\n", 2);
// 		exit(1);
// 	}
// 	return (0);
// }

// int	main(int ac, char **av)
// {
// 	t_game	game;

// 	if (ac == 2)
// 	{
// 		check_filetype(av[1]);
// 		parsing(av[1], &game);
// 	}
// }

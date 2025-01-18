/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:22:39 by armitite          #+#    #+#             */
/*   Updated: 2025/01/18 20:34:28 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	check_pixels(char **pixel_data)
{
	int	check1;
	int	check2;
	int	pixel;

	if (!pixel_data[0])
		return(-1);
	check1 = ft_atoi(&pixel_data[0][1]);
	check2 = ft_atoi(pixel_data[1]);
	pixel = ft_atoi(pixel_data[2]);
	if (check1 != 64 || check2 != 64)
		return (-1);
	if (pixel < 1)
		return (-1);
	return (pixel);
}

int	get_pixels(int fd, int number, t_wall *wall)
{
	int		i;
	char	*line;

	i = 0;
	wall->col = malloc(sizeof(t_col) * number);
	while (i < number)
	{
		line = get_next_line(fd);
		wall->col[i].c = line[1];
		wall->col[i].id = ft_atoi_base(&line[6], "0123456789ABCDEF");
		free(line);
		i++;
	}
	return (0);
}

int	make_walls(int fd, int number, t_wall *wall)
{
	int	i;

	i = 0;
	get_pixels(fd, number, wall);
	wall->wall = malloc(sizeof(char *) * 64);
	wall->wall[i] = get_next_line(fd);
	free(wall->wall[i]);
	while (i < 64)
	{
		wall->wall[i] = get_next_line(fd);
		wall->wall[i] = ft_strtrim(wall->wall[i], "\n");
		wall->wall[i] = ft_strtrim(wall->wall[i], ",");
		wall->wall[i] = ft_strtrim(wall->wall[i], "\"");
		i++;
	}
	return (0);
}

int	parse_xpm(t_wall *wall, char *file)
{
	char	**pixel_data;
	int		fd;
	int		number;
	int		i;
	char	*test;

	fd = ft_open(file);
	test = get_next_line(fd);
	i = -1;
	while (++i < 3)
	{
		free(test);
		test = get_next_line(fd);
	}
	pixel_data = ft_split(test, ' ');
	number = check_pixels(pixel_data);
	wall->info = number;
	if (number == -1)
		return (ft_free(pixel_data), free(test), close(fd), 1);
	make_walls(fd, number, wall);
	ft_free(pixel_data);
	free(test);
	close(fd);
	return (0);
}

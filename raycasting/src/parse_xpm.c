/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:22:39 by armitite          #+#    #+#             */
/*   Updated: 2025/01/12 23:45:59 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_pixels(char **pixel_data)
{
	int	check1;
	int	check2;
	int	pixel;
	
	pixel_data[0] = ft_strchr_g(pixel_data[0], '"');
	check1 = ft_atoi(pixel_data[0]);
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
	int i;

	i = 0;
	wall->pixels = malloc(sizeof(char *) * number);
	while (i < number)
	{
		wall->pixels[i] = get_next_line(fd);
		wall->pixels[i] = ft_strtrim(wall->pixels[i], "\n");
		wall->pixels[i] = ft_strtrim(wall->pixels[i], "\"");
		printf("%s\n", wall->pixels[i]);
		i++;
	}
	return (0);
}

int make_walls(int fd, int number, t_wall *wall)
{
	int i;
	
	i = 0;
	get_pixels(fd, number, wall);
	wall->wall = malloc(sizeof(char *) * 64);
	get_next_line(fd);
	while (i < 64)
	{
		wall->wall[i] = get_next_line(fd);
		wall->wall[i] = ft_strtrim(wall->wall[i], "\n");
		wall->wall[i] = ft_strtrim(wall->wall[i], ",");
		wall->wall[i] = ft_strtrim(wall->wall[i], "\"");
		//printf("%s\n", wall->wall[i]);
		i++;
	}
	return (0);
}

int	parse_xpm(t_wall *wall, char **av)
{
	char **pixel_data;
	int	fd;
	int number;
	int	i;
	char *test;
	
	i = 0;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		perror("File error");
	while (i < 4)
	{
		test = get_next_line(fd);
		i++;
	}
	pixel_data = ft_split(test, ' ');
	number = check_pixels(pixel_data);
	if (number == -1)
		return (printf("Eroor"), 1);
	make_walls(fd, number, wall);
	return (0);
}

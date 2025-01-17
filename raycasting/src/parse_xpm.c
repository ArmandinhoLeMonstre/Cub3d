/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:22:39 by armitite          #+#    #+#             */
/*   Updated: 2025/01/17 15:39:59 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	check_pixels(char **pixel_data)
{
	int	check1;
	int	check2;
	int	pixel;

	pixel_data[0] = ft_strchr_g(pixel_data[0], '"');
	printf("stat %s\n", pixel_data[0]);
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
	int		i;
	char	*line;

	i = 0;
	wall->col = malloc(sizeof(t_col) * number);
	while (i < number)
	{
		line = get_next_line(fd);
		wall->col[i].c = line[1];
		wall->col[i].id = ft_atoi_base(&line[6], "0123456789ABCDEF");
		printf("%c | %d\n", wall->col[i].c, wall->col[i].id);
		free(line);
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

int	parse_xpm(t_wall *wall, char *file)
{
	char **pixel_data;
	int	fd;
	int number;
	int	i;
	char *test;

	i = 0;
	printf("file : %s\n", file);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror("File error");
	test = get_next_line(fd);
	while (i < 3)
	{
		free(test);
		test = get_next_line(fd);
		i++;
	}
	printf("test : %s\n", test);
	pixel_data = ft_split(test, ' ');
	number = check_pixels(pixel_data);
	wall->info = number;
	if (number == -1)
		return (printf("Error\n"), 1);
	make_walls(fd, number, wall);
	close(fd);
	return (0);
}
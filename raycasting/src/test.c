/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:47:09 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/15 22:55:45 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 25);
	map[0] = "111111111111111111111111";
	map[1] = "100000000000000000000001";
	map[2] = "100000000000000000000001";
	map[3] = "100000222220000303030001";
	map[4] = "100000200020000000000001";
	map[5] = "100000200020000300030001";
	map[6] = "100000200020000000000001";
	map[7] = "100000220220000303030001";
	map[8] = "100000000000000000000001";
	map[9] = "100000000000000000000001";
	map[10] = "100000000000000000000001";
	map[11] = "100000000000000000000001";
	map[12] = "100000000000000000000001";
	map[13] = "100000000000000000000001";
	map[14] = "100000000000000000000001";
	map[15] = "144444444000000000000001";
	map[16] = "140400004000000000000001";
	map[17] = "140000504000000000000001";
	map[18] = "140400004000000000000001";
	map[19] = "140444444000000000000001";
	map[20] = "140000000000000000000001";
	map[21] = "144444444000000000000001";
	map[22] = "100000000000000000000001";
	map[23] = "111111111111111111111111";
  map[24] = NULL;
  return (map);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void peutetre(t_game *game)
{
	int	x;

	x = -1;
	while (++x < WIDTH - 1)
	{
		// printf("x : %d\n", x);
		double cameraX = 2 * x / (double)WIDTH - 1; // Camera space coordinate
		double rayDirX = game->p1.dirx + game->p1.planex * cameraX;
		double rayDirY = game->p1.diry + game->p1.planey * cameraX;
		printf("raydirx = %F | raydirY = %F\n", rayDirX, rayDirY);

		//which box of the map we're in
		int mapX = (int) game->p1.posx;
		int mapY = (int) game->p1.posy;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		printf("deltadisX : %F | deltadisY : %F\n", deltaDistX, deltaDistY);

		int stepX, stepY;
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = ( game->p1.posx - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 -  game->p1.posx) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = ( game->p1.posy - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 -  game->p1.posy) * deltaDistY;
		}

		int hit = 0, side; // was a NS or a EW wall hit?
		while (!hit) {
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (mapX < 0)
				mapX = 0;
			printf("mapx : %d | mapy : %d\n", mapX, mapY);
			if (game->map.map[mapX][mapY] > '0')
			{
				// printf("oui\n");
				hit = 1; // Check for wall hit
			}
		}
		// Calculate distance to the wal
		double perpWallDist;
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else 
			perpWallDist = (sideDistY - deltaDistY);
		printf("prepawall %F\n", perpWallDist);
		int lineHeight = (int)(HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int	y;
		y = drawStart - 1;
		// printf("y = %d | drawend :%d\n", y, drawEnd);
		while (++y <= drawEnd)
		{
			int color =  0xFFFF00;
			if(side == 1)
				color = color / 2;
			my_mlx_pixel_put(&game->img, x, y, 0xFFFF00);
		}
	}
}

void	game_loop(t_game *game)
{
	peutetre(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_loop(game->mlx);
}

void init_player(t_game *game)
{
	game->p1.posx = 22;
	game->p1.posy = 12;
	game->p1.dirx = -1;
	game->p1.diry = 0;
	game->p1.planex = 0;
	game->p1.planey = 0.66;
}

int main(void)
{
	t_game	game;

	init_player(&game);
	game.map.map = get_map();
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3d");
	game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
			&game.img.line_length, &game.img.endian);
	game_loop(&game);
}

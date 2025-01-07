/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:48:07 by armitite          #+#    #+#             */
/*   Updated: 2025/01/07 18:54:13 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int	draw_player(int x, int y, int size, t_data *data)
{
	int	i;
	int color;

	color = 0xFF;
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(data, x + i, y, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(data, x, y + i, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(data, x + i, y + size, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(data, x + size, y + i, color);
		i++;
	}
	return(0);
}

void    put_square(t_data *data)
{
    int x;
    int y;
    int longueur;
    int long_calc;
    int largeur;
    int larg_calc;

    x = 0;
    y = 0;
    longueur = 0;
    largeur = 0;
    long_calc = (64 * longueur);
    larg_calc = (64 * largeur);
    
    while (longueur < 17)
    {
		largeur = 0;
		while (largeur < 30)
        {
			y = 0;
			while ((y + long_calc < (64 + long_calc)))
			{
				x = 0;
				while ((x + larg_calc < (64 + larg_calc)))
				{
					my_mlx_pixel_put(data, x + (64 * largeur), y + (64 * longueur), 0x00FF0000);
					x++;
				}
				y++;
			}
			largeur++;
		}
        longueur++;
    }
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    // int x;
    // int y;

    // x = 0;
    // y = 0;
    // while (y < 64)
    // {
    //     x = 0;
    //     while (x < 64)
    //     {
    //         my_mlx_pixel_put(&img, x, y, 0x00FF0000);
    //         x++;
    //     }
    //     y++;
    // }
    //put_square(&img);
	draw_player(1920 / 2, 1080 / 2, 16, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:43:45 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/08 21:32:01 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../mlx_linux/mlx.h"
#include "../libft/include/libft.h"

typedef struct s_sprites
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	int		*floor;
	int		*ceiling;
}	t_sprites;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_game
{
	t_mlx		mlx;
	t_sprites	sprites;
}	t_game;
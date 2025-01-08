#include "../include/cub3d.h"

void	init_player(t_player *player)
{
	player->x = (1920 / 2);
	printf("%f\n", player->x);
	player->y = (1080 / 2);
	printf("%f\n", player->y);

	player->p_up = 0;
	player->p_dw = 0;
	player->p_lf = 0;
	player->p_rg = 0;
}

void	move_player(t_player *player)
{
	int	movement;

	movement = 5;
	if(player->p_up == 1)
		player->y -= movement;
	if(player->p_dw == 1)
		player->y += movement;
	if(player->p_lf == 1)
		player->x -= movement;
	if(player->p_rg == 1)
		player->x += movement;
}
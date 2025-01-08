#include "../include/cub3d.h"

int	key_true(int keycode, t_player *player)
{
	printf("%d\n", keycode);
	if (keycode == 119)
		player->p_up = 1;
	if (keycode == 115)
		player->p_dw = 1;
	if (keycode == 97)
		player->p_lf = 1;
	if (keycode == 100)
		player->p_rg = 1;
	return (0);
}

int	key_false(int keycode, t_player *player)
{
	if (keycode == 119)
		player->p_up = 0;
	if (keycode == 115)
		player->p_dw = 0;
	if (keycode == 97)
		player->p_lf = 0;
	if (keycode == 100)
		player->p_rg = 0;
	return (0);
}
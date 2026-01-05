/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:15:12 by msabir            #+#    #+#             */
/*   Updated: 2026/01/03 02:56:56 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	minimap_fill_rect(t_game *game, t_minimap_rect rect)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;

	y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			screen_x = rect.x + x;
			screen_y = rect.y + y;
			if (screen_x >= 0 && screen_x < SCREEN_W
				&& screen_y >= 0 && screen_y < SCREEN_H)
				my_mlx_pixel_put(game, screen_x, screen_y, rect.color);
			x++;
		}
		y++;
	}
}

int	minimap_tile_color(t_game *game, int row, int col)
{
	if (row < 0 || row >= game->data.map_height
		|| col < 0 || col >= game->data.map_width)
		return (0x1b1b1b);
	if (game->data.map[row][col] == 1)
		return (0xdfdfdf);
	return (0x3a3a3a);
}

void	minimap_draw_single_tile(t_game *game, int row_off, int col_off)
{
	t_minimap_rect	rect;
	int				map_row;
	int				map_col;

	rect.x = MM_POS_X + (col_off + MM_VIEW) * MM_TILE;
	rect.y = MM_POS_Y + (row_off + MM_VIEW) * MM_TILE;
	rect.w = MM_TILE;
	rect.h = MM_TILE;
	map_row = (int)game->player.pos_y + row_off;
	map_col = (int)game->player.pos_x + col_off;
	rect.color = minimap_tile_color(game, map_row, map_col);
	minimap_fill_rect(game, rect);
}

void	minimap_draw_player_pixel(t_game *game, int x, int y, int radius)
{
	int	screen_x;
	int	screen_y;

	if (x * x + y * y > radius * radius)
		return ;
	screen_x = MM_POS_X + MM_VIEW * MM_TILE + MM_TILE / 2 + x;
	screen_y = MM_POS_Y + MM_VIEW * MM_TILE + MM_TILE / 2 + y;
	if (screen_x >= 0 && screen_x < SCREEN_W
		&& screen_y >= 0 && screen_y < SCREEN_H)
		my_mlx_pixel_put(game, screen_x, screen_y, 0xFFE26B);
}

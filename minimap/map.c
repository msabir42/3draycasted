/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:45:07 by msabir            #+#    #+#             */
/*   Updated: 2026/01/03 02:58:11 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_tiles(t_game *game)
{
	int	row;
	int	col;

	row = -MM_VIEW;
	while (row <= MM_VIEW)
	{
		col = -MM_VIEW;
		while (col <= MM_VIEW)
		{
			minimap_draw_single_tile(game, row, col);
			col++;
		}
		row++;
	}
}

static void	draw_player_marker(t_game *game)
{
	int	marker_radius;
	int	x;
	int	y;

	marker_radius = MM_TILE / 3;
	y = -marker_radius;
	while (y <= marker_radius)
	{
		x = -marker_radius;
		while (x <= marker_radius)
		{
			minimap_draw_player_pixel(game, x, y, marker_radius);
			x++;
		}
		y++;
	}
}

void	minimap(t_game *game)
{
	t_minimap_rect	rect;
	int				grid_size;

	grid_size = (MM_VIEW * 2 + 1) * MM_TILE;

	rect.x = MM_POS_X - 2;
	rect.y = MM_POS_Y - 2;
	rect.w = grid_size + 4;
	rect.h = grid_size + 4;
	rect.color = 0x111111;
	minimap_fill_rect(game, rect);

	rect.x = MM_POS_X - 1;
	rect.y = MM_POS_Y - 1;
	rect.w = grid_size + 2;
	rect.h = grid_size + 2;
	rect.color = 0x202020;
	minimap_fill_rect(game, rect);

	draw_tiles(game);
	draw_player_marker(game);
}

void	draw_map(t_game *game)
{
	minimap(game);
}

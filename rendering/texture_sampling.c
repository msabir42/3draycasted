#include "../include/cub3d.h"

int	get_texture_color(t_texture *tex, int x, int y)
{
	int color;
	char *pixel;

	if (!tex || !tex->addr)
		return (0x0000FF);
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	color = *(int *)pixel;
	return (color);
}
#include "../cub3d.h"
#include <math.h>

double	wall_projection_height(t_ray *ray)
{
	double	projection_height;
	double	dist_to_projection_plane;

	dist_to_projection_plane = (SCREEN_W / 2) / tan(FOV / 2);
	if (ray->dist < 0.05)
		ray->dist = 0.05;
	if (ray->dist > 100)
		ray->dist = 100;
	if (isnan(ray->dist) || isinf(ray->dist))
		ray->dist = 1.0;
	projection_height = (0.5 * dist_to_projection_plane) / ray->dist;
	if (projection_height > SCREEN_H * 10)
		projection_height = SCREEN_H * 10;
	if (projection_height < 1)
		projection_height = 1.0;
	if (isnan(projection_height) || isinf(projection_height))
		projection_height = SCREEN_H / 2;
	return (projection_height);
}

int	get_texture_color(t_texture *tex, int x, int y)
{
	int		color;
	char	*pixel;

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

void	draw_textured_slice(t_game *game, int x, double wall_height,
		t_intersect hit, t_ray *ray)
{
	int			wall_top;
	int			wall_bottom;
	int			y;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			tex_x;
	int			color;
	t_texture	*texture;
	double		wall_x;

	// for debugging my textures implemeantion
	printf("Slice %d: wall_height=%.2f, dist=%.3f\n", x, wall_height,
			ray->dist);
	if (wall_height <= 0.1 || isnan(wall_height) || isinf(wall_height))
		wall_height = SCREEN_H / 2;
	if (wall_height > SCREEN_H * 10)
		wall_height = SCREEN_H * 10;
	if (ray->side == 0)
	{
		texture = ray->facing_right ? &game->east_tex : &game->west_tex;
		wall_x = hit.hit_point_y - floor(hit.hit_point_y);
		tex_x = (int)(wall_x * texture->width);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= texture->width)
			tex_x = texture->width - 1;
	}
	else
	{
		texture = ray->facing_down ? &game->south_tex : &game->north_tex;
		wall_x = hit.hit_point_x - floor(hit.hit_point_x);
		tex_x = (int)(wall_x * texture->width);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= texture->width)
			tex_x = texture->width - 1;
	}
	if (!texture || !texture->img || !texture->addr || texture->width <= 0
		|| texture->height <= 0)
	{
		printf("ERROR: Texture not loaded properly!\n");
		return ;
	}
	wall_top = (SCREEN_H / 2) - (wall_height / 2);
	wall_bottom = (SCREEN_H / 2) + (wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > SCREEN_H)
		wall_bottom = SCREEN_H;
	if (wall_top >= wall_bottom)
	{
		printf("ERROR: Invalid wall dimensions: top=%d, bottom=%d\n", wall_top,
				wall_bottom);
		return ;
	}
	if (wall_height < 1.0)
		wall_height = 1.0;
	step = (double)texture->height / wall_height;
	if (isnan(step) || isinf(step) || step <= 0)
		step = 1.0;
	tex_pos = (wall_top - SCREEN_H / 2 + wall_height / 2) * step;
	if (tex_pos < 0)
		tex_pos = 0;
	y = wall_top;
	while (y < wall_bottom)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		color = get_texture_color(texture, tex_x, tex_y);
		my_mlx_pixel_put(game, x, y, color);
		tex_pos += step;
		y++;
	}
}

void	draw_slice_to_screen(t_game *game, double ray_angle, int x)
{
	t_ray		ray;
	t_intersect	final_hit;
	double		wall_height;
	double		player_angle;
	double		angle_diff;

	while (ray_angle < 0)
		ray_angle += 2 * M_PI;
	while (ray_angle > 2 * M_PI)
		ray_angle -= 2 * M_PI;
	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	ray.angle = ray_angle;
	ray.found_wall = false;
	ray_direction(&ray);
	final_hit = calculate_distance(game, &game->player, &ray);
	angle_diff = player_angle - ray_angle;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	if (ray.dist < 0.05)
		ray.dist = 0.05;
	if (ray.dist > 100)
		ray.dist = 100;
	if (isnan(ray.dist) || isinf(ray.dist))
		ray.dist = 1.0;
	ray.dist *= cos(angle_diff);
	if (ray.dist < 0.05)
		ray.dist = 0.05;
	if (ray.found_wall)
	{
		wall_height = wall_projection_height(&ray);
		draw_textured_slice(game, x, wall_height, final_hit, &ray);
	}
	else
	{
		printf("No wall found for ray %d\n", x);
	}
}

void	draw_walls(t_game *game)
{
	double ray_angle;
	double angle_step;
	double player_angle;
	double start_angle;
	int i;

	i = 0;
	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	start_angle = player_angle - (FOV / 2);
	angle_step = FOV / NUM_RAYS;

	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + (i * angle_step);
		draw_slice_to_screen(game, ray_angle, i);
		i++;
	}
}
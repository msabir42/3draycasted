
NAME			= cub3D
NAME_BONUS		= cub3D_bonus
CC				= cc
CFLAGS			= -Wall -Werror -Wextra
INCLUDE_FLAGS	= -Iinclude -Iminilibx-linux
MLX_FLAGS		= -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz


PARSING_SRCS = parsing/check_wall.c \
               parsing/fetch_lines.c \
               parsing/fetch_lines_helper.c \
               parsing/init_data.c \
               parsing/parse_colors.c \
               parsing/parse_colors_utils.c \
               parsing/parse_map.c \
               parsing/parse_map_split.c \
               parsing/parse_map_helpers.c \
               parsing/parse_metadata.c \
               parsing/parse_metadata_utils.c \
               parsing/utils_error.c \
               parsing/utils_sanitize.c \
               parsing/utils_string.c \
               parsing/validate_map.c \
               parsing/utils_split.c \
               parsing/utils_gnl.c \
               parsing/utils_memory.c \
               parsing/utils_more_string.c \
               parsing/helpers.c \
               parsing/check_connectivity.c \
               parsing/check_duplicate.c \
               parsing/debug.c

RAYCASTING_SRCS = raycasting/init_environment.c \
                  raycasting/intersections.c \
                  raycasting/intersections_helper.c \
                  raycasting/mlx_init.c \
                  raycasting/player.c \
                  raycasting/player_movement.c \
                  raycasting/player_rotation.c \
                  raycasting/player_rotation_helper.c \
                  raycasting/raycasting.c \
                  raycasting/helpers.c

RENDERING_SRCS = rendering/draw_slice.c \
                 rendering/draw_texture_slice.c \
                 rendering/draw_walls.c \
                 rendering/texture_sampling.c \
                 rendering/wall_projection.c \
                 rendering/textures.c \
                 rendering/draw_slice_pixels.c \
                 rendering/free_textures.c

MANDATORY_SRCS = main.c $(PARSING_SRCS) $(RAYCASTING_SRCS) $(RENDERING_SRCS)


BONUS_SRCS = bonus/main_bonus.c \
             bonus/parsing/check_wall_bonus.c \
             bonus/parsing/fetch_lines_bonus.c \
             bonus/parsing/fetch_lines_helper_bonus.c \
             bonus/parsing/init_data_bonus.c \
             bonus/parsing/parse_colors_bonus.c \
             bonus/parsing/parse_colors_utils_bonus.c \
             bonus/parsing/parse_map_bonus.c \
             bonus/parsing/parse_map_split_bonus.c \
             bonus/parsing/parse_map_helpers_bonus.c \
             bonus/parsing/parse_metadata_bonus.c \
             bonus/parsing/parse_metadata_utils_bonus.c \
             bonus/parsing/utils_error_bonus.c \
             bonus/parsing/utils_sanitize_bonus.c \
             bonus/parsing/utils_string_bonus.c \
             bonus/parsing/validate_map_bonus.c \
             bonus/parsing/utils_split_bonus.c \
             bonus/parsing/utils_gnl_bonus.c \
             bonus/parsing/utils_memory_bonus.c \
             bonus/parsing/utils_more_string_bonus.c \
             bonus/parsing/helpers_bonus.c \
             bonus/parsing/check_connectivity_bonus.c \
             bonus/parsing/check_duplicate_bonus.c \
             bonus/parsing/debug_bonus.c \
             bonus/raycasting/init_environment_bonus.c \
             bonus/raycasting/intersections_bonus.c \
             bonus/raycasting/intersections_helper_bonus.c \
             bonus/raycasting/mlx_init_bonus.c \
             bonus/raycasting/player_bonus.c \
             bonus/raycasting/player_movement_bonus.c \
             bonus/raycasting/player_rotation_bonus.c \
             bonus/raycasting/player_rotation_helper_bonus.c \
             bonus/raycasting/raycasting_bonus.c \
             bonus/raycasting/helpers_bonus.c \
             bonus/raycasting/mouse_bonus.c \
             bonus/minimap/map_bonus.c \
             bonus/minimap/map_helpers_bonus.c \
             bonus/rendering/draw_slice_bonus.c \
             bonus/rendering/draw_texture_slice_bonus.c \
             bonus/rendering/draw_walls_bonus.c \
             bonus/rendering/texture_sampling_bonus.c \
             bonus/rendering/wall_projection_bonus.c \
             bonus/rendering/textures_bonus.c \
             bonus/rendering/draw_slice_pixels_bonus.c \
             bonus/rendering/free_textures_bonus.c


MANDATORY_OBJS	= $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS		= $(BONUS_SRCS:.c=.o)


all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(MANDATORY_OBJS)
	$(CC) $(MANDATORY_OBJS) $(MLX_FLAGS) -o $(NAME)

$(NAME_BONUS): $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(MLX_FLAGS) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re


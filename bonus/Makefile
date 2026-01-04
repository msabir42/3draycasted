NAME = cub3D_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz

PARSING_SRCS = parsing/check_wall.c \
               parsing/fetch_lines.c \
               parsing/init_data.c \
               parsing/parse_colors.c \
               parsing/parse_colors_utils.c \
               parsing/parse_map.c \
               parsing/parse_map_utils.c \
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
                  raycasting/mlx_init.c \
                  raycasting/player.c \
                  raycasting/player_movement.c \
                  raycasting/player_rotation.c \
                  raycasting/raycasting.c\
                  raycasting/helpers.c\
                  minimap/map.c \
                  minimap/map_helpers.c \
                  raycasting/mouse.c

RENDERING_SRCS = rendering/draw_slice.c \
                 rendering/draw_texture_slice.c \
                 rendering/draw_walls.c \
                 rendering/texture_sampling.c \
                 rendering/wall_projection.c \
                 rendering/textures.c \
                 rendering/draw_slice_pixels.c \
                 rendering/free_textures.c


MAIN_SRC = main.c

SRCS = $(MAIN_SRC) $(PARSING_SRCS) $(RAYCASTING_SRCS) $(RENDERING_SRCS) 
OBJS = $(SRCS:.c=.o)

all: $(NAME)

bonus: $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -Iminilibx-linux -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean bonus

.PHONY: all clean fclean re

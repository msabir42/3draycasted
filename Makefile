NAME = cube
CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz

# Source files
PARSING_SRCS = parsing.c utils.c textures.c
RAYCASTING_SRCS = raycasting/player_rotation.c raycasting/intersections.c raycasting/raycasting.c \
                  raycasting/init_environment.c raycasting/mlx_init.c raycasting/player.c \
                  raycasting/player_movement.c
RENDERING_SRCS = rendering/walls.c

SRCS = main.c $(PARSING_SRCS) $(RAYCASTING_SRCS) $(RENDERING_SRCS)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
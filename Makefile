NAME = cube

SRCS = main.c\
	raycasting/init_environment.c\
	raycasting/mlx_init.c\
	raycasting/player.c\
	raycasting/player_movement.c\
	raycasting/player_rotation.c\
	raycasting/intersections.c\
	raycasting/raycasting.c\
	rendering/walls.c


OBJS = $(SRCS:.c=.o)

MLX = -L minilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz 
CC = cc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
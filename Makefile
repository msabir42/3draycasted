NAME = cube

SRCS = main.c\
	

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
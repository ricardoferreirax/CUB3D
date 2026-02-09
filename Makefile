# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
#    Updated: 2026/02/09 21:10:57 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Wpedantic -Wshadow -Wdouble-promotion -Wformat=2 -Wstrict-aliasing=2 \
		-fno-omit-frame-pointer \
		-g -fsanitize=undefined 
		
#  MLX_CFLAGS= -Wall -Wextra -Werror

MLX_CFLAGS = -Wall -Wextra -Werror \
	-Wno-return-type \
	-Wno-sign-compare \
	-Wno-unused-parameter \
	-Wno-parentheses \
	-Wno-unused-variable \
	-Wno-unused-but-set-variable

INCS    = -Iinclude -Ilibft

LIBFT   = libft/libft.a
MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx.a

SRC_FILES = main.c \
	aux_funcs.c  \
	ghosts.c \
	init/init.c \
	init/init_aux_funcs.c \
	init/init_ghosts.c \
	time.c \
	init/init_defaults.c \
	execution/player_collision.c \
	execution/player_rotation.c \
	execution/player_movement.c \
	execution/wrap_port.c \
	execution/minimap.c \
	execution/put_pixel.c  \
	execution/render_frame.c \
	parsing/map_dimensions.c \
	parsing/map_read.c \
	parsing/map_validate_closed.c \
	parsing/map_player.c \
	parsing/map_validate_chars.c \
	init/init_mlx.c execution/raycasting.c \
	execution/raycasting_utils.c \
	math/math.c \
	hooks/handle_close.c \
	hooks/handle_keys.c \
	utils/free.c  \

OBJ_DIR   = objs
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLX) -lXext -lX11 -lm -g -o $(NAME)


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

# $(MLX):
# 	make -C $(MLX_PATH) CFLAGS="$(MLX_CFLAGS)"

$(MLX):
	$(MAKE) -C $(MLX_PATH)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
e: all clean
	clear
.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
#    Updated: 2026/01/18 16:35:17 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d

CC      = cc
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
SRC_FILES = execution/init_defaults.c execution/start_execution.c execution/init_map_3d.c \
			execution/init_mlx.c execution/render_3d.c hooks/handle_close.c hooks/handle_keys.c \
			hooks/init_hooks.c utils/free.c main.c

OBJ_DIR   = objs
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLX) -lXext -lX11 -g -o $(NAME)


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

# $(MLX):
# 	make -C $(MLX_PATH) CFLAGS="$(MLX_CFLAGS)"

$(MLX):
	$(MAKE) -C $(MLX_PATH) -f Makefile.gen CC=$(CC) CFLAGS="$(MLX_CFLAGS)"

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

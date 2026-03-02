# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2026/02/21 23:51:28 by rmedeiro         ###   ########.fr        #
=======
#    Updated: 2026/03/02 09:33:24 by rmedeiro         ###   ########.fr        #
>>>>>>> ricardo
#                                                                              #
# **************************************************************************** #

NAME    = cub3d

CC      = clang-12
CFLAGS  = -Wall -Wextra -Werror -Wpedantic -Wshadow -Wdouble-promotion -Wformat=2 -Wstrict-aliasing=2 \
		-fno-omit-frame-pointer \
		-g 
#-fsanitize=undefined 
		
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
	srcs/init/init.c \
	srcs/init/init_cub3d.c \
	srcs/init/init_mlx.c \
	srcs/init/init_ghosts.c \
	srcs/init/init_sprites.c \
	time.c \
	srcs/map/map_load.c \
	srcs/map/map_dimensions.c \
	srcs/map/map_read.c \
	srcs/map/map_validate_grid.c \
	srcs/map/map_parse_lines.c \
	srcs/map/map_ghost.c \
	srcs/map/map_wrap.c \
	srcs/map/minimap_test.c \
	srcs/map/map_utils.c \
	srcs/text/texture_parse_path.c \
	srcs/text/texture_parse_floor_ceiling.c \
	srcs/text/texture_load.c \
	srcs/text/texture_pick_wall.c \
	srcs/text/texture_utils.c \
	srcs/render/render_frame.c \
	srcs/render/render_wall_texture.c \
	srcs/render/sprite_draw.c \
	srcs/render/render_sprites.c \
	srcs/render/render_floor_texture.c \
	srcs/render/render_ceiling_texture.c \
	srcs/render/render_utils.c \
	srcs/render/render_menu.c \
	srcs/render/process_raycasting.c \
	srcs/render/render_center_hit.c \
	srcs/render/sprite_draw_col.c \
	srcs/render/perform_dda.c \
	srcs/render/render_fill_color.c \
	srcs/player/player_collision.c \
	srcs/player/player_rotation.c \
	srcs/player/player_movement.c \
	srcs/player/handle_gate_toggle.c \
	srcs/player/player_collect_pacdots.c \
	srcs/player/player_spawn.c \
	srcs/hooks/handle_close.c \
	srcs/hooks/handle_keys.c \
	utils/free.c  \
	rendering/pixels.c \

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

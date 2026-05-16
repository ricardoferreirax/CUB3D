# **************************************************************************** #
#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
#    Updated: 2026/05/14 22:36:07 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d

CC      = gcc
CFLAGS  = -O3 -Wall -Wextra -Werror -Wshadow -Wdouble-promotion  \
		  -Wformat=2 -Wstrict-aliasing=2 -fno-omit-frame-pointer -g
		   
ASAN_FLAGS = -fsanitize=address
UBSAN_FLAGS = -fsanitize=undefined

INCS    = -Iinclude -Ilibft

LIBFT   = libft/libft.a
MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx.a

SRC_FILES = main.c \
srcs/hooks/handle_close.c \
srcs/hooks/handle_mouse.c \
srcs/hooks/handle_gate_toggle.c \
srcs/hooks/controller_player.c \
srcs/hooks/handle_keys.c \
srcs/init/init_sprites.c \
srcs/init/init_base.c \
srcs/init/parse.c \
srcs/init/helper.c \
srcs/init/init.c \
srcs/init/init_ghosts.c \
srcs/init/init_map.c \
srcs/init/init_mlx.c \
srcs/init/init_player.c \
srcs/init/init_spritesheet.c \
srcs/map/utils.c \
srcs/map/grid.c \
srcs/map/flood_fill.c \
srcs/map/ghost.c \
srcs/map/load.c \
srcs/map/map_cub_prefix.c \
srcs/map/parse_lines.c \
srcs/map/read.c \
srcs/map/validate_bounds.c \
srcs/map/wrap.c \
srcs/player/actions.c \
srcs/player/apply_move.c \
srcs/player/collect_pacdots.c \
srcs/player/controller.c \
srcs/player/touch_ghost.c \
srcs/player/collision.c \
srcs/player/move.c \
srcs/player/spawn.c \
srcs/render/render_frame.c \
srcs/render/render_plane.c \
srcs/render/render_debug_symbols.c \
srcs/render/raycast_find_wall.c \
srcs/render/raycast_frame.c \
srcs/render/render_collectibles.c \
srcs/render/render_ghosts.c \
srcs/render/render_into_framebuffer.c \
srcs/textures/pick_wall.c \
srcs/textures/parse_color.c \
srcs/textures/parse_pacman.c \
srcs/textures/load.c \
srcs/textures/set_texture_path.c \
srcs/textures/parse_cube_texture.c \
srcs/textures/parse_path.c \
srcs/textures/utils.c \
srcs/base/bitmasking.c \
srcs/base/constructor.c \
srcs/base/helpers.c \
srcs/base/disambiguation.c \
srcs/clock/time.c \
srcs/ghosts/sprites.c \
srcs/ghosts/ghost_ai.c \
srcs/ghosts/helpers.c \
srcs/ghosts/math.c \
srcs/ghosts/penhouse.c \
srcs/ghosts/targetting.c \
srcs/ghosts/chose_next_dir.c \
srcs/ghosts/update.c \
srcs/utils/free.c \
srcs/utils/free_helpers.c \
srcs/utils/funny_funcs.c \
srcs/utils/helpers.c \
srcs/utils/math_funcs.c \
srcs/utils/render_utils.c \
srcs/debug/ray_debug_draw.c \
srcs/debug/ray_debug_cast.c \
srcs/draw/background.c \
srcs/draw/menu.c \
srcs/draw/pacman_sprites.c \
srcs/draw/plane.c \
srcs/draw/utils.c \
srcs/draw/build_sprite_box.c \
srcs/draw/sprite_column.c \
srcs/draw/wall_column.c

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

$(MLX):
	$(MAKE) -C $(MLX_PATH)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=mlx.supp -s \
		./$(NAME) maps/Pacman.cub

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

e: all clean
	clear
a:
	$(MAKE) CFLAGS="$(CFLAGS) $(ASAN_FLAGS)" e

u:
	$(MAKE) CFLAGS="$(CFLAGS) $(UBSAN_FLAGS)" e
	
.PHONY: all clean fclean re val

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
#    Updated: 2026/05/06 17:18:32 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d

CC      = gcc -Og
CFLAGS  = -Wall -Wextra -Werror -Wpedantic -Wshadow -Wdouble-promotion  -Wformat=2 -Wstrict-aliasing=2 \
		-fno-omit-frame-pointer \
		-g 
#-fsanitize=undefined 
		
#  MLX_CFLAGS= -Wall -Wextra -Werror

MLX_CFLAGS = -Wall -Wextra -Werror \
	-Wno-return-type \
	-Wno-sign-compare \
	-Wno-unused-parameter \
	-Wno-parentheses\
	-Wno-unused-variable \
	-Wno-unused-but-set-variable

INCS    = -Iinclude -Ilibft

LIBFT   = libft/libft.a
MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx.a

SRC_FILES = main.c \
	srcs/hooks/handle_close.c \
	srcs/hooks/handle_gate_toggle.c \
	srcs/hooks/handle_keys.c \
	srcs/hooks/handle_mouse.c \
	srcs/init/init_mlx.c \
	srcs/init/init_spritesheet.c \
	srcs/init/init_sprites.c \
	srcs/init/init.c \
	srcs/init/init_base.c \
	srcs/init/init_ghosts.c \
	srcs/map/map_read.c \
	srcs/map/map_utils.c \
	srcs/map/map_load.c \
	srcs/map/map_wrap.c \
	srcs/map/map_ghost.c \
	srcs/map/map_validate_grid.c \
	srcs/map/map_parse_lines.c \
	srcs/player/player_collision.c \
	srcs/player/player_collect_pacdots.c \
	srcs/player/player_controller.c \
	srcs/player/player_spawn.c \
	srcs/render/raycast_frame.c \
	srcs/render/render_center_hit.c \
	srcs/render/raycast_dda.c \
	srcs/render/render_utils.c \
	srcs/render/render_plane.c \
	srcs/render/draw_plane.c \
	srcs/render/render_debug_symbols.c \
	srcs/render/render_frame.c \
	srcs/render/render_into_framebuffer.c \
	srcs/render/render_sprites.c \
	srcs/draw/draw_background.c \
	srcs/draw/draw_wall_column.c \
	srcs/draw/draw_menu.c \
	srcs/draw/draw_sprite.c \
	srcs/draw/draw_sprite_column.c \
	srcs/textures/texture_parse_color.c \
	srcs/textures/texture_utils.c \
	srcs/textures/texture_load.c \
	srcs/textures/texture_parse_path.c \
	srcs/textures/texture_pick_wall.c \
	srcs/debug/ray_debug_cast.c \
	srcs/debug/ray_debug_line.c \
	srcs/debug/ray_debug_render.c \
	srcs/debug/ray_debug_utils.c \
	srcs/debug/ray_debug_draw.c \
	srcs/utils/helpers.c \
	srcs/utils/free.c \
	srcs/utils/render_utils.c \
	srcs/base/base_constructor.c \
	srcs/base/base_bitmasking.c \
	srcs/ghosts/ghost_ai.c \
	srcs/ghosts/sprites.c  \
	srcs/clock/time.c

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

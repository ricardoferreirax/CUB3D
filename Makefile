# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:34:39 by rmedeiro          #+#    #+#              #
#    Updated: 2026/03/11 21:19:17 by rmedeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3d

CC      = clang-12 -O3
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
	aux_funcs.c  \
	srcs/init/init.c \
	srcs/init/init_base.c \
	srcs/init/init_spritesheet.c \
	srcs/init/init_mlx.c \
	srcs/init/init_ghosts.c \
	srcs/init/init_sprites.c \
	time.c \
	srcs/map/map_load.c \
	srcs/map/map_read.c \
	srcs/map/map_validate_grid.c \
	srcs/map/map_parse_lines.c \
	srcs/map/map_ghost.c \
	srcs/map/map_wrap.c \
	srcs/map/map_utils.c \
	srcs/textures/texture_parse_path.c \
	srcs/textures/texture_parse_color.c \
	srcs/textures/texture_load.c \
	srcs/textures/texture_pick_wall.c \
	srcs/textures/texture_utils.c \
	srcs/render/render_frame.c \
	srcs/render/render_wall_texture.c \
	srcs/render/sprite_draw.c \
	srcs/render/render_sprites.c \
	srcs/render/render_floor_ceiling.c \
	srcs/render/render_utils.c \
	srcs/render/render_menu.c \
	srcs/render/raycast_frame.c \
	srcs/render/render_center_hit.c \
	srcs/render/sprite_draw_col.c \
	srcs/render/raycast_dda.c \
	srcs/render/render_fill_color.c \
	srcs/render/debug_raycast.c \
	srcs/player/player_collision.c \
	srcs/player/player_controller.c \
	srcs/player/player_collect_pacdots.c \
	srcs/player/player_spawn.c \
	srcs/hooks/handle_close.c \
	srcs/hooks/handle_keys.c \
	srcs/hooks/handle_gate_toggle.c \
	srcs/hooks/handle_mouse.c \
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

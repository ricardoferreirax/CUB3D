/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:18:06 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/11 19:47:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_E 101
# define KEY_H 104
#define KEY_M 109
# define KEY_1 49
# define KEY_2 50

#define MOUSE_SENS 0.00001

typedef struct s_game	t_game;

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	esc;
	int	e;
	int	e_lock;
	int	mouse_lock;
	int mouse_hidden;
}	t_key;

int		handle_close(t_game *g);
int		handle_key_press(int keycode, t_game *g);
int		handle_key_release(int keycode, t_game *g);
void	handle_gate_toggle(t_game *g);
int		handle_mouse_move(int x, int y, t_game *g);
void	center_mouse(t_game *g);

#endif

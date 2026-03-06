/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:41:18 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/03/05 10:30:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	map_tile_type(char t, int tile_type)
{
	if (tile_type == TILE_WALL)
		return (t == WALL || t == 'M');
	if (tile_type == TILE_VOID)
		return (t == VOID);
	if (tile_type == TILE_SOLID)
		return (t == WALL || t == 'M' || t == GATE);
	if (tile_type == TILE_WALKABLE)
	{
		return (t == OPEN_SPACE || t == PACDOT || t == ENERGIZER
			|| t == WRAP_PORTS
			|| t == 'N' || t == 'S' || t == 'E' || t == 'W');
	}
	return (0);
}

int	map_row_last_col(t_game *g, int row, int want_wrap)
{
	int		last;
	char	*s;

	if (!g || !g->map.grid || row < 0 || row >= g->map.height)
		return (-1);
	s = g->map.grid[row];
	last = (int)ft_strlen(s) - 1; // começa no último índice da string (antes do '\0')
	while (last >= 0 && (s[last] == '\n')) // ignora as '\n' no final da row
		last--;
	if (!want_wrap) // se não queremos uma row com wrap 
		return (last);
	if (last < 1 || s[0] != WRAP_PORTS || s[last] != WRAP_PORTS) // se as extremidades da row não forem wrap ou se a row não tiver pelo menos 2 colunas
		return (-1);
	return (last); // devolve o índice da última coluna (antes do '\n')
}

char	map_get_tile(t_game *game, int row, int col)
{
	int	last_col;

	if (!game || !game->map.grid || row < 0 || row >= game->map.height)
		return (VOID);
	last_col = map_row_last_col(game, row, 1);
	if (last_col >= 0) // se a row tem wrap ajusta a coluna para permitir o wrap
	{
		if (col < 0)
			col = last_col;
		else if (col > last_col)
			col = 0;
	}
	else // se a row no tem wrap verifica se a coluna esta dentro dos limites e se o tile nessa posição e válido
		last_col = map_row_last_col(game, row, 0);
	if (col < 0 || col > last_col || game->map.grid[row][col] <= ' ') // se a coluna esta fora dos limites ou se o tile é um espaço
		return (VOID);
	return (game->map.grid[row][col]); // devolve o tile na posição (row, col)
}

int	map_is_empty_line(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != '\n' && s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

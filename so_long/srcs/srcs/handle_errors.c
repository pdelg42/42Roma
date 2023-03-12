/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:21:50 by aperrone          #+#    #+#             */
/*   Updated: 2022/02/17 08:21:52 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	check_map(t_game *game, char *line, int current)
{
	if (check_char_map(line, current))
	{
		ft_putstr("Invalid map - Invalid character");
		exit (0);
		return (1);
	}
	if (game->win->win_size.x == -1)
		game->win->win_size.x = (int)ft_strlen(line);
	if ((int)ft_strlen(line) != game->win->win_size.x)
	{
		ft_putstr("Invalid map - Line dimension");
		exit (0);
		return (1);
	}
	return (0);
}

int	check_char_map(char *line, int curr)
{
	int	i;

	i = 0;
	while (curr == 0 && (line[i] != '\n'))
	{
		if (line[i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'P' && line[i] != 'C'
			&& line[i] != 'E' && line[i] != 'Q')
			return (1);
		i++;
	}
	if (line[i - 1] != '1' || line[0] != '1')
		return (1);
	return (0);
}

void	check_square(int x, int y)
{
	if (x == y)
	{
		ft_putstr("Invalid map - Square map");
		exit (0);
	}
}

void	check_onerow(int y)
{
	if (y < 3)
	{
		ft_putstr("Invalid map");
		exit (0);
	}
}

int	check_position(t_vector a, t_vector b)
{
	if (a.x == b.x && a.y == b.y)
		return (1);
	return (0);
}

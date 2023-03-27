/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:19:01 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/27 17:38:01 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	close_game(t_cub *cub)
{
	if (!cub->mlx)
		exit(1);
	if (!cub->win)
		exit(1);
	mlx_destroy_window(cub->mlx, cub->win);
	freematrix(cub->map, row_counter(cub->map));
	if (!cub->data)
		exit(1);
	free(cub->data);
	exit(0);
	return (0);
}

int game_init(t_cub *cub)
{
	t_data	*d;

	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (0);
	cub->win = mlx_new_window(cub->mlx, WIN_SIZE_W, WIN_SIZE_H, "cub3d");
	if (!cub->win)
		return (0);
	d = (t_data *) ft_calloc(sizeof(t_data), 1);
	if (!d)
		return (0);
	cub->data = d;
	return (1);
}

int main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2)
		return (1);
	if (!game_init(&cub))
		close_game(&cub);
	if (!parse_map(&cub, argv[1]))
		close_game(&cub);
	render(&cub);
	mlx_hook(cub.win, 17, 0, close_game, &cub);
	mlx_loop(cub.mlx);
	return (0);
}

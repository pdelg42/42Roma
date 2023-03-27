/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:19:01 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/27 11:58:59 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int    close_game(t_cub *cub)
{
    mlx_destroy_window(cub->mlx, cub->win);
    exit(0);
    return (0);
}

int game_init(t_cub *cub)
{
    t_data *d;


    cub->mlx = mlx_init();
    if (!cub->mlx)
        return (0);
    d = (t_data *) ft_calloc();
    return (1);
}

int main(int argc, char **argv)
{
    t_cub cub;

    if (!game_init(&cub))
        return (1);
    cub.win = mlx_new_window(cub.mlx, 1000, 500, "cub3d");
    render(&cub);
    mlx_hook(cub.win, 17, 0, close_game, &cub);
    mlx_loop(cub.mlx);
    return (0);
}

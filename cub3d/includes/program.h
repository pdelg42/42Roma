/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:46:26 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/27 16:42:26 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

# include "libft.h"
# include "listft.h"

# include "../mlx/mlx.h"
# include "get_next_line.h"

# define WIN_SIZE_W 1028
# define WIN_SIZE_H 720

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_cub
{
    t_data  *data;
    void    *mlx;
    void    *win;
	char	*str_tmp;
	char	**map;
}   t_cub;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    render(t_cub *cub);
int		parse_map(t_cub *cub, char *map_path);

#endif

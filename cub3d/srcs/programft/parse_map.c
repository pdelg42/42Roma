/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:27:24 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/27 17:38:19 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int validate_file(char *map_path)
{
	char *s;

	s = ft_strstr(map_path, ".cub");
	if (!s || ft_strcmp(s, ".cub"))
		return (-1);
	return (open(map_path, O_RDONLY));
}

int	parse_map(t_cub *cub, char *map_path)
{
	int		fd;
	char	*tmp;
	
	fd = validate_file(map_path);
	if (fd < 0)
		return (0);
	tmp = get_next_line(fd);
	cub->str_tmp = (char *) ft_calloc(1, 1);
	while (tmp)
	{
		cub->str_tmp = ft_strjoin(cub->str_tmp, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	cub->map = ft_split(cub->str_tmp, '\n');
	free(cub->str_tmp);
	return (1);
}
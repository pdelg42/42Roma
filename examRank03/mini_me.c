/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:05:34 by aperrone          #+#    #+#             */
/*   Updated: 2023/01/03 11:10:06 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ERR1 "Error: argument\n"
#define ERR2 "Error: Operation file corrupted\n"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(const char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	check_pos(float x, float y, float x_0, float y_0, float radius)
{
	float d;

	d = sqrtf(pow(x - x_0, 2.) + pow(y - y_0, 2.));
	if (d <= radius)
	{
		if((radius - d) < 1.0)
			return (0);
		return (1);
	}
	return (2);
}

int	main(int argc, char	**argv)
{
	FILE	*file;
	char	*c;
	char	b;
	char	id, color;
	int		x, y;
	int		b_w, b_h;
	int		read, pos;
	float	x_0, y_0, radius;

	if (argc != 2)
		return (ft_error(ERR1));
	if (!(file = fopen(argv[1], "r"))
			|| (fscanf(file, "%d %d %c\n", &b_w, &b_h, &b) != 3)
			|| (!(b_w > 0 && b_w <= 300 && b_h > 0 && b_h <= 300))
			|| (!(c = malloc(sizeof(char) * (b_w * b_h)))))
		return (ft_error(ERR2));
	memset(c, b, b_w * b_h);
	while ((read = fscanf(file, "%c %f %f %f %c\n", &id, &x_0, &y_0, &radius, &color)) == 5)
	{
		if (!(radius > 0) || !(id == 'c' || id == 'C'))
			break ;
		y = -1;
		while (++y < b_h)
		{
			x = -1;
			while (++x < b_w)
			{
				pos = check_pos((float)x, (float)y, x_0, y_0, radius);
				if (pos == 0 || (pos == 1 && id == 'C'))
					c[y * b_w + x] = color;
			}
		}
	}
	if (read != -1)
	{
		free(c);
		return (ft_error(ERR2));
	}
	y = -1;
	while (++y < b_h)
	{
		write(1, c + y * b_w, b_w);
		write(1, "\n", 1);
	}
	free(c);
	fclose(file);
	return (0);
}

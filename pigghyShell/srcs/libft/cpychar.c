/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpychar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:09:45 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/22 07:13:22 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	cpychar_gen(char *str, int i, char **out)
{
	char	c[2];

	c[0] = str[i];
	c[1] = '\0';
	*out = ft_strjoin(*out, c);
}

void	cpychar(t_minish *minish, int i)
{
	char	c[2];

	c[0] = minish->input[i];
	c[1] = '\0';
	minish->temporary = ft_strjoin(minish->temporary, c);
}

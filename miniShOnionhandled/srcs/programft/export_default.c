/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 04:01:23 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/09 09:33:11 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	swap(t_minish *minish, int i, int j)
{
	char	*temp;

	if (ft_strcmp(minish->ft_env[i], minish->ft_env[j]) > 0)
	{
		temp = minish->ft_env[i];
		minish->ft_env[i] = minish->ft_env[j];
		minish->ft_env[j] = temp;
	}
}

void	default_export(t_minish *minish)
{
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	len = minish->env_list->prev->id;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			swap(minish, i, j);
			j++;
		}
		i++;
	}
	k = 0;
	while (minish->ft_env[k])
		printf("%s\n", minish->ft_env[k++]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_blood.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 05:41:07 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 09:46:40 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	first_blood(t_minish *minish)
{
	if (minish->argv_list)
	{
		if (ft_strcmp(minish->argv_list->box, "cd") == 0)
			if (cd_b(minish))
				return (1);
		if (ft_strcmp(minish->argv_list->box, "export") == 0)
			if (export(minish))
				return (1);
		if (ft_strcmp(minish->argv_list->box, "unset") == 0)
			if (unset(minish))
				return (1);
		if (ft_strcmp(minish->argv_list->box, "exit") == 0)
			exit_b(minish);
	}
	return (0);
}

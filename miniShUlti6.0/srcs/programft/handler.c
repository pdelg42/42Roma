/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:44:36 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/13 19:52:55 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	absolute_handler(t_minish *minish)
{
	if (minish->argv_list)
	{
		minish->skipper = minish->argv_list;
		minish->len = len_list(&minish->argv_list);
		while ((minish->len)-- && !pipe_compare(minish->skipper->box))
		{
			if (minish->skipper->status & 1)
			{
				minish->skipper->status &= -2;
				minish->cmd = ft_strdup(minish->skipper->box);
				return (1);
			}
			minish->skipper = minish->skipper->next;
		}
	}
	return (0);
}

int	relative_handler(t_minish *minish)
{
	t_node	*skppr;

	if (minish->argv_list)
	{
		skppr = minish->argv_list;
		minish->len = len_list(&minish->argv_list);
		while (minish->len-- && !pipe_compare(skppr->box))
		{
			if (skppr->status & 2)
			{
				skppr->status &= -3;
				minish->cmd = ft_strdup(skppr->box);
				return (1);
			}
			skppr = skppr->next;
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existence.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:09:45 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/08 19:43:45 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	existence(t_minish *minish)
{
	t_node	*skipper;
	int		len;

	skipper = minish->env_list;
	len = minish->env_list->prev->id;
	while (skipper && len--)
	{
		if (ft_strcmp(skipper->type, minish->key) == 0)
			return (1);
		skipper = skipper->next;
	}
	return (0);
}

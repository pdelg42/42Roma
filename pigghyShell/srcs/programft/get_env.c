/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:47:58 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 06:50:57 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

char	*fetch_env(t_minish *minish)
{
	return (ft_substr(minish->env_list->box,
			ft_strlen(minish->env_list->type) + 1,
			ft_strlen(minish->env_list->box)));
}

char	*get_env(t_minish *minish, char	*query)
{
	if (!minish->argv_list)
		return (NULL);
	minish->skipper = minish->env_list;
	minish->len = minish->env_list->prev->id;
	while (minish->skipper && (minish->len)--
		&& ft_strcmp(minish->skipper->type, query))
		minish->skipper = minish->skipper->next;
	if ((minish->len) != 0)
		minish->temporary = ft_substr(minish->skipper->box,
				ft_strlen(minish->skipper->type) + 1,
				ft_strlen(minish->skipper->box));
	return (minish->temporary);
}

int	get_dist_from_anchor(t_node *l)
{
	int	i;

	i = 0;
	while (!(l->status & 0x100))
		l = l->next;
	while (l->id != 1)
	{
		l = l->next;
		i++;
	}
	return (i);
}

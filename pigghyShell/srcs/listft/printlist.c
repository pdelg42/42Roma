/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:09:14 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 13:59:00 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	printlist(t_node **h)
{
	t_node	*tmp;

	if (!*h)
	{
		write(2, "emptyList\n", 11);
		return ;
	}
	tmp = *h;
	while (tmp->next != *h)
	{
		fprintf(stderr, "[%p][%3d][%s][%s][%d]\n", tmp, tmp->id,
			tmp->box, tmp->type, tmp->status);
		tmp = tmp->next;
	}
	fprintf(stderr, "[%p][%3d][%s][%s][%d]\n\n", tmp, tmp->id,
		tmp->box, tmp->type, tmp->status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:26:17 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/22 15:35:00 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

t_node	*new_(char *content, int id)
{
	t_node	*temp;

	temp = calloc(sizeof(t_node), 1);
	temp->id = id;
	temp->status = 0;
	temp->box = ft_strdup(content);
	temp->type = key_fetcher(content);
	temp->next = temp;
	temp->prev = temp;
	return (temp);
}

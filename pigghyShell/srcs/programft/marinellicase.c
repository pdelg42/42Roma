/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marinellicase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:43:33 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/25 08:43:57 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	casual_free(t_minish **minish)
{
	free((*minish)->key);
	free((*minish)->value);
	(*minish)->key = NULL;
	(*minish)->value = NULL;
}

void	marinellicase(t_minish *minish)
{
	minish->temporary = ft_strjoin(ft_strdup(minish->key), "=");
	minish->temporary = ft_strjoin(minish->temporary, minish->value);
	add_t(&minish->env_list,
		new_(minish->temporary, minish->env_list->prev->id + 1));
	freestr(minish->temporary);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:26:34 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/09 09:37:52 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	set_paths(t_minish *minish)
{
	minish->skipper = minish->env_list;
	minish->len = minish->env_list->prev->id;
	while (ft_strcmp(minish->skipper->type, "PATH"))
		minish->skipper = minish->skipper->next;
	minish->value = ft_substr(minish->skipper->box,
			ft_strlen(minish->skipper->type) + 1,
			ft_strlen(minish->skipper->box));
	free(minish->skipper->box);
	minish->skipper->box = ft_strjoin(ft_strdup(minish->skipper->type), "=");
	minish->skipper->box = ft_strjoin(minish->skipper->box,
			minish->system_path);
	minish->skipper->box = ft_strjoin(minish->skipper->box, "/builtins:");
	minish->skipper->box = ft_strjoin(minish->skipper->box, minish->value);
	free(minish->value);
	minish->value = NULL;
}

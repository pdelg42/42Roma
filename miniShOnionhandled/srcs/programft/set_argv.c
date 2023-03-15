/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 08:30:49 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/09 07:39:18 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	set_argv_sub(t_minish *minish)
{
	char	*temp;
	int		i;

	i = -1;
	temp = calloc(sizeof(char), 1);
	while (minish->argv_list->next->box[++i])
	{
		if (minish->argv_list->next->box[i] == '\"')
		{
			if (minish->argv_list->next->box[i - 1] == ' '
				|| minish->argv_list->next->box[i + 1] == '\"')
				i++;
		}
		else
			cpychar_gen(minish->argv_list->next->box, i, &temp);
	}
	freestr(minish->argv_list->next->box);
	minish->argv_list->next->box = ft_strdup(temp);
	freestr(temp);
}

t_node	**set_argv(t_minish *minish)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (minish->temp[k])
		add_t(&minish->argv_list, new_(minish->temp[k++], ++i));
	relister(&minish->argv_list);
	freematrix(minish->temp, row_counter(minish->temp));
	if (minish->argv_list)
		if (ft_strcmp(minish->argv_list->box, "export") == 0)
			set_argv_sub(minish);
	return (&minish->argv_list);
}

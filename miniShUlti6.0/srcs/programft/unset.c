/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:51:12 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/09 10:35:56 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	identifier_unset_control(char *box)
{
	int	i;

	i = 0;
	while (box[i])
	{
		if (!ft_isdigit(box[i]) && !ft_isalpha(box[i]))
		{
			printf("%s: %s: %s: not a valid identifier\n", ">>> ", "unset", box);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset(t_minish *minish)
{
	t_node	*temp;
	int		len;

	temp = minish->argv_list;
	len = minish->argv_list->prev->id;
	temp = temp->next;
	while (temp && --len)
	{
		if (identifier_unset_control(temp->box))
			return (1);
		if (src_in_list(&minish->env_list, temp->box))
		{
			free(minish->env_list->box);
			free(minish->env_list->type);
			del_h(&minish->env_list);
			relister(&minish->env_list);
		}
		temp = temp->next;
	}
	return (1);
}

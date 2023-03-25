/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_sub2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:34:47 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 14:32:43 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	case_sub2(t_minish *minish)
{
	char	*temp;

	minish->temporary = ft_substr(minish->env_list->box, 0,
			ft_strlen(minish->env_list->box));
	temp = ft_substr(minish->value, 1, ft_strlen(minish->value));
	minish->temporary = ft_strjoin(minish->temporary, "=\"");
	minish->temporary = ft_strjoin(minish->temporary, temp);
	freestr(minish->env_list->type);
	free(minish->env_list->box);
	del_h(&minish->env_list);
	free(temp);
}

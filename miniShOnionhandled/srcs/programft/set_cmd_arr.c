/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:47:00 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/14 11:11:52 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	paths_loop(t_minish *minish, int a, int len)
{
	src_in_list(&minish->argv_list, "CMD");
	if (!absolute_handler(minish) && !relative_handler(minish))
		get_paths(minish);
	if (minish->cmd)
	{
		minish->argv_list = minish->argv_list->next;
		minish->cmd_arr[a - len - 1] = ft_strdup(minish->cmd);
		minish->cmd_arr[a - len] = NULL;
		freestr(minish->cmd);
	}
	else
	{
		minish->cmd_arr[a - len - 1] = ft_strdup("");
		minish->cmd_arr[a - len] = NULL;
	}
}

int	set_cmd_arr(t_minish *minish)
{
	int	len;
	int	a;

	len = 0;
	if (!minish->argv_list || !minish->argv_list->type)
		return (0);
	minish->skipper = minish->argv_list;
	while (minish->skipper && !(minish->skipper->next->status & ANCHOR))
	{
		len += !ft_strcmp(minish->skipper->type, "CMD");
		minish->skipper = minish->skipper->next;
	}
	len += !ft_strcmp(minish->skipper->type, "CMD");
	minish->cmd_arr = malloc(sizeof(char *) * (len + 1));
	a = len;
	while (len-- > 0)
		paths_loop (minish, a, len);
	minish->cmd = minish->cmd_arr[0];
	return (1);
}

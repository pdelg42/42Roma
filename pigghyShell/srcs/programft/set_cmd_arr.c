/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:47:00 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 06:29:19 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	checks(t_minish *minish)
{
	if (!minish->argv_list || (minish->argv_list->next->id == 1
			&& (redir_compare(minish->argv_list->box)
				|| append_compare(minish->argv_list->box)
				|| heredoc_compare(minish->argv_list->box))))
		return (1);
	return (0);
}

void	paths_loop(t_minish *minish, int a, int len)
{
	if (!absolute_handler(minish) && !relative_handler(minish))
		get_paths(minish);
	if (minish->cmd != NULL)
	{
		minish->argv_list = minish->argv_list->next;
		src_in_list(&minish->argv_list, "CMD");
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
	if (checks(minish))
		return (0);
	minish->skipper = minish->argv_list;
	while (minish->skipper && !(minish->skipper->next->status & ANCHOR))
	{
		len += !ft_strcmp(minish->skipper->type, "CMD");
		minish->skipper = minish->skipper->next;
	}
	len += !ft_strcmp(minish->skipper->type, "CMD");
	minish->cmd_arr = calloc(sizeof(char *), (len + 1));
	a = len;
	minish->cmd_arr[0] = NULL;
	src_in_list(&minish->argv_list, "CMD");
	while (len-- > 0)
		paths_loop (minish, a, len);
	minish->cmd = minish->cmd_arr[0];
	minish->argv_list = minish->argv_list->next;
	relister(&minish->argv_list);
	return (1);
}

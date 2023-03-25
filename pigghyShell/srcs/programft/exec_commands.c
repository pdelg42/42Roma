/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:38:12 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/24 15:25:35 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

static int	check_cmd_exist(t_node *l)
{
	int	len;

	len = len_list(&l);
	while (len-- > 0 && ft_strcmp(l->type, "PIPE")
		&& !(l->next->status & 0x100))
	{
		if (!ft_strcmp(l->type, "CMD"))
			return (1);
		l = l->next;
	}	
	if (!ft_strcmp(l->type, "CMD"))
		return (1);
	return (0);
}

static t_node	*get_args_list(t_minish *ms, t_node *l, int flag)
{
	t_node	*args_list;
	int		len;

	args_list = NULL;
	if (flag)
		add_t(&args_list, new_(ms->cmd, l->id));
	if (l->prev->id == l->id)
		return (args_list);
	len = len_list(&l);
	while (len-- > 0 && ft_strcmp(l->next->type, "PIPE")
		&& !(l->next->status & 0x100))
	{
		if (!ft_strcmp(l->type, "ARG"))
			add_t(&args_list, new_(l->box, l->id));
		l = l->next;
	}
	if (!ft_strcmp(l->type, "ARG"))
		add_t(&args_list, new_(l->box, l->id));
	relister(&args_list);
	return (args_list);
}

void	do_reds(t_minish *minish)
{
	int	do_r;

	do_r = 0;
	while (!(minish->argv_list->next->status & 0x100)
		&& !pipe_compare(minish->argv_list->box))
	{
		if (!ft_strcmp(minish->argv_list->type, "HEREDOC"))
		{
			do_r |= 1;
			break ;
		}
		if (!ft_strcmp(minish->argv_list->type, "REDIR")
			|| !ft_strcmp(minish->argv_list->type, "APPEND"))
			do_r |= 2;
		minish->argv_list = minish->argv_list->next;
	}
	if (do_r & 1)
		heredoc(minish->argv_list->next, minish);
	else if (do_r & 2)
		redir(minish->argv_list->next, minish);
}

int	exec_command(t_minish *minish)
{
	t_node	*args_list;
	int		cmd_exist;

	if (!minish->argv_list)
		return (127 << 8);
	relister(&minish->argv_list);
	cmd_exist = check_cmd_exist(minish->argv_list);
	args_list = get_args_list(minish, minish->argv_list, cmd_exist);
	minish->temp = list_to_matrix(&args_list);
	freenode(args_list);
	do_reds(minish);
	if (!cmd_exist)
	{
		minish->cmd = NULL;
		return (0xfe << 8);
	}
	else if (builtin_compare(minish->argv_list->box))
		return (0xfe << 8);
	else if ((execve(minish->cmd, minish->temp, minish->ft_env) < 0))
		return (0x7f << 8);
	return (0xff << 8);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:38:12 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/16 00:06:26 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

static int	check_cmd_exist(t_node *l)
{
	int	len;

	len = len_list(&l);
	while (len-- > 0 && ft_strcmp(l->type, "PIPE"))
	{
		if (!ft_strcmp(l->type, "CMD"))
			return (1);
		l = l->next;
	}	
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
	return (args_list);
}

int	exec_command(t_minish *minish)
{
	t_node	*args_list;
	int		cmd_exist;
	// int i = 0;
	// while (minish->cmd_arr[i])
	// 	printf("ARG: %s\n", minish->cmd_arr[i++]);
	if (!fork())
	{
		if (!minish->argv_list)
			return (127);
		cmd_exist = check_cmd_exist(minish->argv_list);
		args_list = get_args_list(minish, minish->argv_list, cmd_exist);
		// printf("Exec command\n");
		// printlist(&args_list);
		minish->temp = list_to_matrix(&args_list);
		printf("TEMP %s %s %s\n", minish->temp[0], minish->temp[1], minish->temp[2]);
		if (src_in_list(&minish->argv_list, "HEREDOC"))
			heredoc(minish->argv_list->next, minish);
		else if (src_in_list(&minish->argv_list, "REDIR")
			|| src_in_list(&minish->argv_list, "APPEND"))
			redir(minish->argv_list->next, minish);
		if (!cmd_exist)
		{
			minish->cmd = ft_strdup(minish->argv_list->box);
			return (0);
		}
		else if ((execve(minish->cmd, minish->temp, minish->ft_env) < 0))
			return (127);
		// else if (builtin_compare(minish->argv_list->box))
		// 	return (1);
		list_point_to(&minish->argv_list, 1);
		exit(0);
	}
	waitpid(-1, 0, 0);
	return (0);
}

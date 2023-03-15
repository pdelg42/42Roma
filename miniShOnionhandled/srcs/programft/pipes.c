/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:29:37 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/16 00:03:19 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

/*
	sarà necessario eseguire tutti i comandi contemporaneamente creando ogni 
	volta un pid diverso e cambiando il fd di uscita del prossimo elemento
*/

void	list_point_to_status(t_node **list, int status)
{
	while (!((*list)->status & status))
		*list = (*list)->next;
}

void	do_pipes(t_minish *minish, int *i)
{
	int		end[2];

	pipe(end);
	minish->cmd = minish->cmd_arr[*i];
	printf("CMD %s\n", minish->cmd);
	if (fork() == 0)
	{
		close(end[0]);
		if (*i == minish->n_pipes)
			dup2(minish->stdout_cpy, STDOUT_FILENO);
		else
			dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		exec_command(minish);
		exit(0);
		// break ;
	}
	else
	{
		dup2(end[0], STDIN_FILENO);
		close(end[0]);
		close(end[1]);
	}
	(*i)++;
}

void	exec_pipeline(t_minish *minish, pid_t *pid)
{
	int		prev_fd[2];
	int		i;
	t_node	*tmp_node;
	int		tmp;

	if (!minish->argv_list)
		return ;
	list_point_to_status(&minish->argv_list, 0x100);
	minish->n_pipes = 0;
	while (!(minish->argv_list->next->status & 0x100))
	{
		if (!ft_strcmp(minish->argv_list->type, "PIPE"))
			minish->n_pipes++;
		minish->argv_list = minish->argv_list->next;
	}
	list_point_to_status(&minish->argv_list, 0x100);
	printf("N PIPES %d\n", minish->n_pipes);
	if (minish->n_pipes > 0)
	{
		i = 0;
		tmp = minish->n_pipes;
		while (tmp >= 0)
		{
			do_pipes(minish, &i);
			tmp--;
		}
		while(tmp++ < minish->n_pipes)
			waitpid(-1, 0, 0);
		dup2(minish->stdin_cpy, STDIN_FILENO);
	}
	else
		exec_command(minish);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:29:37 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/13 22:06:26 by aperrone         ###   ########.fr       */
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

void	exec_pipeline(t_minish *minish, pid_t *pid)
{
	int		prev_fd[2];
	int		i;
	t_node	*tmp_node;

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
	i = 0;
	prev_fd[0] = dup(minish->stdin_cpy);
	prev_fd[1] = dup(minish->stdout_cpy);
	while (i++ <= minish->n_pipes)
	{
		if (pipe(minish->pipefd))
			return ;
		*pid = fork();
		if (*pid == 0)
		{
			minish->cmd = minish->cmd_arr[i - 1];
			dup2(prev_fd[0], STDIN_FILENO);
			close(prev_fd[0]);
			close(minish->pipefd[0]);
			dup2(minish->pipefd[1], STDOUT_FILENO);
			close(minish->pipefd[1]);
			break ;
		}
		minish->pids[i - 1] = *pid;
		minish->pids[i] = 0;
		close(prev_fd[0]);
		prev_fd[0] = dup(minish->pipefd[0]);
		close(minish->pipefd[0]);
		close(minish->pipefd[1]);
		src_in_list(&minish->argv_list, "PIPE");
		minish->argv_list = minish->argv_list->next;
	}
	if ((i - 1) >= minish->n_pipes && *pid == 0)
		dup2(minish->stdout_cpy, STDOUT_FILENO);
}

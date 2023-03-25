/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:51:25 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/23 14:16:03 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"
// initiate fd as error 

static void	init_fd(int *fd)
{
	fd[1] = dup(STDOUT_FILENO);
	fd[0] = dup(STDIN_FILENO);
}

// close all fd in fd list or force a specific one (-1 to close all)

static void	close_all(int *fd, int force)
{
	if (force == 1 || force == -1)
		close(fd[1]);
	if (force == 0 || force == -1)
		close(fd[0]);
}

// open fd based on type passed

static void	open_as(t_node *f_n, int *fd)
{
	if (!ft_strcmp(f_n->prev->type, "REDIR"))
	{
		if (!ft_strcmp(f_n->prev->box, ">"))
		{
			close_all(fd, 1);
			fd[1] = open(f_n->box, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else
		{
			close_all(fd, 0);
			fd[0] = open(f_n->box, O_RDONLY | O_CREAT, 0644);
		}
	}
	else
	{
		close_all(fd, 1);
		fd[1] = open(f_n->box, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}

void	redir(t_node *file_node, t_minish *minish)
{
	init_fd(minish->file_fd);
	src_in_list(&file_node, "FILE");
	open_as(file_node, minish->file_fd);
	while (!(file_node->status & 0x100) && !pipe_compare(file_node->box))
	{
		if (append_compare(file_node->box) || redir_compare(file_node->box))
			open_as(file_node->next, minish->file_fd);
		if (minish->file_fd[INPUT] < 0 && minish->file_fd[OUTPUT] < 0)
			perror("ERROR");
		file_node = file_node->next;
	}
	dup2(minish->file_fd[1], STDOUT_FILENO);
	dup2(minish->file_fd[0], STDIN_FILENO);
	freematrix(minish->ft_env, row_counter(minish->ft_env));
}

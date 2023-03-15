/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:51:25 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/15 23:23:08 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"
// initiate fd as error 

static void	init_fd(int *fd)
{
	fd[OUTPUT] = -1;
	fd[INPUT] = -1;
}

// close all fd in fd list or force a specific one (-1 to close all)

static void	close_all(int *fd, int force)
{
	if (fd[OUTPUT] > 0 && (force == OUTPUT || force == -1))
		close(fd[OUTPUT]);
	if (fd[INPUT] > 0 && (force == INPUT || force == -1))
		close(fd[INPUT]);
}

// open fd based on type passed

static void	open_as(t_node *f_n, int *fd)
{
	if (!ft_strcmp(f_n->prev->type, "REDIR"))
	{
		if (!ft_strcmp(f_n->prev->box, ">"))
		{
			close_all(fd, OUTPUT);
			fd[OUTPUT] = open(f_n->box, O_RDWR | O_CREAT | O_TRUNC, 0666);
		}
		else
		{
			close_all(fd, INPUT);
			fd[INPUT] = open(f_n->box, O_RDWR | O_CREAT, 0666);
		}
	}
	else
	{
		close_all(fd, OUTPUT);
		fd[OUTPUT] = open(f_n->box, O_RDWR | O_CREAT | O_APPEND, 0666);
	}
}

void	redir(t_node *file_node, t_minish *minish)
{
	int		file_fd[2];
	t_node	*tmp;

	init_fd(file_fd);
	open_as(file_node, file_fd);
	//write(minish->stdout_cpy, ft_itoa(minish->sono_pipe_n), 10);
	//write(minish->stdout_cpy, "\n", 1);
	file_node = file_node->next;
	while (!(file_node->prev->status & 0x100) && ft_strcmp(file_node->type, "PIPE"))
	{
		if (append_compare(file_node->box) || redir_compare(file_node->box))
			open_as(file_node->next, file_fd);
		if (file_fd[INPUT] <= 0 && file_fd[OUTPUT] <= 0)
			perror("ERROR");
		if (file_fd[OUTPUT] >= 0)
			dup2(file_fd[OUTPUT], STDOUT_FILENO);
		if (file_fd[INPUT] >= 0)
			dup2(file_fd[INPUT], STDIN_FILENO);
		file_node = file_node->next;
	}
	freematrix(minish->ft_env, row_counter(minish->ft_env));
	close_all(file_fd, -1);
}

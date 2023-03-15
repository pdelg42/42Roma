/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 07:11:19 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/02 11:51:49 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	heredoc(t_node *eof, t_minish *minish)
{
	char	*line;
	int		fd;

	fd = open(TMPFILE, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	line = readline("> ");
	while (ft_strcmp(line, eof->box))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = readline("> ");
	}
	close(fd);
	list_point_to(&minish->argv_list, 1);
	src_in_list(&minish->argv_list, "HEREDOC");
	minish->argv_list->box = ft_strdup("<");
	minish->argv_list->type = "REDIR";
	minish->argv_list = minish->argv_list->next;
	minish->argv_list->box = ft_strdup(TMPFILE);
	minish->argv_list->type = "FILE";
	list_point_to(&minish->argv_list, 1);
	src_in_list(&minish->argv_list, "FILE");
	exec_command(minish);
	return (0);
}

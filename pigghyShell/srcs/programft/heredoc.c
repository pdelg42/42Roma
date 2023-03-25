/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 07:11:19 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/23 14:37:34 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	heredoc(t_node *eof, t_minish *minish)
{
	char	*line;
	int		fd;

	fd = open(TMPFILE, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	line = readline("> ");
	while (ft_strcmp(line, eof->box))
	{
		write(fd, line, ft_strlen(line));
		freestr(line);
		write(fd, "\n", 1);
		line = readline("> ");
	}
	freestr(line);
	close(fd);
	list_point_to(&minish->argv_list, 1);
	src_in_list(&minish->argv_list, "HEREDOC");
	freestr(minish->argv_list->box);
	minish->argv_list->box = ft_strdup("<");
	minish->argv_list->type = "REDIR";
	minish->argv_list = minish->argv_list->next;
	freestr(minish->argv_list->box);
	minish->argv_list->box = ft_strdup(TMPFILE);
	minish->argv_list->type = "FILE";
	list_point_to(&minish->argv_list, 1);
	do_reds(minish);
}

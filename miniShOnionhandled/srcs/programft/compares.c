/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compares.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:16:24 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/09 09:25:20 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	append_compare(char *box)
{
	if (ft_strcmp(box, ">>") == 0)
		return (1);
	return (0);
}

int	builtin_compare(char *box)
{
	if (ft_strcmp(box, "export") == 0
		|| ft_strcmp(box, "unset") == 0
		|| ft_strcmp(box, "exit") == 0)
		return (1);
	return (0);
}

int	heredoc_compare(char *box)
{
	if (ft_strcmp(box, "<<") == 0)
		return (1);
	return (0);
}

int	redir_compare(char *box)
{
	if (ft_strcmp(box, "<") == 0 || ft_strcmp(box, ">") == 0)
		return (1);
	return (0);
}

int	pipe_compare(char *box)
{
	if (ft_strcmp(box, "|") == 0)
		return (1);
	return (0);
}

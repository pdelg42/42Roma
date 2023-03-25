/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 06:48:48 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 06:54:49 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	checks0(t_minish *minish)
{
	if (!redir_compare(minish->ft_argv[0])
		&& !heredoc_compare(minish->ft_argv[0])
		&& !append_compare(minish->ft_argv[0]))
	{
		fprintf(stderr, ">>>: %s: command not found\n", minish->ft_argv[0]);
		minish->cmd = NULL;
		return (1);
	}
	return (0);
}

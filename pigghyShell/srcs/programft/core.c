/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:53:58 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 15:57:26 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	core(t_minish *minish, pid_t *pid)
{
	int	i;

	i = 0;
	if (*pid == -1)
		perror("Fork Failed");
	else if (*pid == 0)
	{
		minish->status = exec_command(minish);
		exit(WEXITSTATUS(minish->status));
	}
	else
		while (minish->pids[i])
			waitpid(minish->pids[i++], &minish->status, 0);
}

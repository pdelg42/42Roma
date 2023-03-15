/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:40:06 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/08 16:40:28 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	exit_b(t_minish *minish)
{
	if (minish->argv_list->prev->id == 1)
		exit(0);
	if (minish->argv_list->prev->id != 1)
		if (permission_denied(minish))
			exit(0);
}

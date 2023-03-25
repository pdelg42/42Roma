/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission_denied.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:16:10 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/09 09:37:32 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	permission_denied(t_minish *minish)
{
	printf("%s: %s: %s: Permission denied\n", minish->name,
		minish->argv_list->box, minish->argv_list->next->box);
	return (1);
}

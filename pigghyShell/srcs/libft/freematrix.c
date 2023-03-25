/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freematrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:27:14 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 13:54:12 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	freematrix(char **splitted, int i)
{
	int	k;

	if (splitted)
	{
		k = -1;
		while (++k < i)
			freestr(splitted[k]);
		free(splitted);
		splitted = NULL;
	}
}

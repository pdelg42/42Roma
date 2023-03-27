/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:36:07 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/03 15:36:48 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	white()
{
	write(1, "\033[1;37m", 8);
}

void	red()
{
	write(1, "\033[1;31m", 8);
}

void	purple()
{
	write(1, "\033[1;35m", 8);
}

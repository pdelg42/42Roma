/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_fetcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:14:13 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/22 15:35:22 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

char	*key_fetcher(char *content)
{
	int		i;
	char	*temp;

	i = -1;
	temp = calloc(sizeof(char), 256);
	while (content[++i] && content[i] != '=')
		temp[i] = content[i];
	temp[i] = 0;
	return (temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 01:17:18 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/05 01:17:50 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	double_env(t_minish *minish, int i)
{
	if (minish->temporary[i] == '$' && ((minish->temporary[i + 1] == '\0'
				|| minish->temporary[i + 1] == ' ')))
	{
		cpychar_gen(minish->temporary, i, &minish->input);
		return (1);
	}
	return (0);
}

int	quotes_to_ignore(t_minish *minish, int i)
{
	if ((minish->temporary[(i)] == '\"'
			&& minish->temporary[(i) + 1] == '\"')
		|| (minish->temporary[(i)] == '\''
			&& minish->temporary[(i) + 1] == '\''))
		return (1);
	return (0);
}

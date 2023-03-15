/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 08:31:24 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/11 15:53:37 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	argv_builder(t_minish *minish)
{
	int	f;

	f = 0;
	minish->s = selector(minish->input, minish->set);
	if (minish->input[0] != '\"' && ++f)
		pre_split(minish);
	else
		minish->input = ft_strtrim(minish->input, "\"");
	minish->temp = ft_split(minish->input, ' ');
	freestr(minish->input);
	minish->ft_argv = list_to_matrix(set_argv(minish));
	minish->ft_env = list_to_matrix(&minish->env_list);
	type_eraser(minish->argv_list);
	tagger(minish);
	if (f)
		post_split(minish);
	if (minish->argv_list)
		minish->argv_list->status |= 0x100;
}

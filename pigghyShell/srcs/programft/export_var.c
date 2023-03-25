/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:14:13 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/25 08:43:52 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	case01(t_minish *minish, int f)
{
	if (f == 0)
		return ;
	src_in_list(&minish->env_list, minish->key);
	if (f == 3 || f == 4)
		case1(minish);
	else if (f == 1)
		case2(minish);
	add_t(&minish->env_list, new_(minish->temporary,
			minish->env_list->prev->id + 1));
	freestr(minish->temporary);
}

void	case0_sub(t_minish *minish)
{
	minish->temporary = ft_strjoin(ft_strdup(minish->key), "=");
	minish->temporary = ft_strjoin(minish->temporary, "\"");
	minish->temporary = ft_strjoin(minish->temporary, "\"");
	add_t(&minish->env_list,
		new_(minish->temporary, minish->env_list->prev->id + 1));
	freestr(minish->temporary);
}

void	case0(t_minish *minish, int f)
{
	if (f == 0)
		add_t(&minish->env_list,
			new_(minish->key, minish->env_list->prev->id + 1));
	else if (f == 1 || f == 2 || f == 3)
		case0_sub(minish);
	else
	{
		minish->temporary = ft_strjoin(ft_strdup(minish->key), "=");
		if (minish->value)
			minish->temporary = ft_strjoin(minish->temporary, minish->value);
		else
		{
			minish->temporary = ft_strjoin(minish->temporary, "\"");
			minish->temporary = ft_strjoin(minish->temporary, "\"");
		}
		add_t(&minish->env_list,
			new_(minish->temporary, minish->env_list->prev->id + 1));
		freestr(minish->temporary);
	}
}

void	export_var(t_minish *minish)
{
	int		f;

	minish->skipper = minish->argv_list->next;
	minish->len = minish->argv_list->prev->id - 1;
	while (minish->skipper && (minish->len)--)
	{
		f = 0;
		if (!get_flag(minish->skipper->box, &f))
			break ;
		get_key(minish, f);
		get_value(minish, minish->skipper->box);
		if (!existence(minish))
		{
			if (f == 1)
				marinellicase(minish);
			else
				case0(minish, f);
		}
		else
			case01(minish, f);
		casual_free(&minish);
		minish->skipper = minish->skipper->next;
	}
}

int	export(t_minish *minish)
{
	minish->cd_flag = 0;
	if (minish->argv_list->prev->id == 1)
		default_export(minish);
	else if (minish->argv_list->next->box[0] == '-')
		permission_denied(minish);
	else if (minish->argv_list->prev->id != 1)
		export_var(minish);
	relister(&minish->env_list);
	return (1);
}

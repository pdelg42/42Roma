/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:57:32 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/10 09:41:24 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

unsigned char	*set_builder(void)
{
	unsigned char	*set;
	unsigned char	i;

	set = NULL;
	set = malloc(sizeof(unsigned char) * 126);
	i = 0;
	while (i++ < 127)
		set[(int)i] = i;
	set[(int)i] = 0;
	return (set);
}

char	selector(char *input, unsigned char *set)
{
	int	h;
	int	k;

	h = 1;
	while (set[h] && h < 126)
	{
		k = 0;
		while (input[k] && k < 126)
		{
			if (input[k] == set[h] && input[k] != '\"' && input[k] != '\''
				&& input[k] != '$' && input[k] != ' ' && input[k] != '>'
				&& input[k] != '<' && input[k] != '|')
				set[h] = '0';
			k++;
		}
		h++;
	}
	k = 33;
	while ((set[k] == '0' || set[k] == '\"' || set[k] == '\''
			|| set[k] == '$' || set[k] == ' ' || set[k] == '>'
			|| set[k] == '<' || set[k] == '|') && k < 126)
		k++;
	return (set[k]);
}

void	skipp_conditions(t_minish *minish, int *i)
{
	while ((minish->double_q) > 0 && minish->input[*i]
		&& (minish->single_q) > 0)
	{
		if (minish->input[*i] == '\'')
			(minish->single_q)--;
		else if (minish->input[*i] == '\"')
			(minish->double_q)--;
		else if (minish->input[*i] == ' ')
			minish->input[*i] = minish->s;
		(*i)++;
	}
}

void	pre_split(t_minish *minish)
{
	int		i;

	i = 0;
	while (minish->input[i])
	{
		if (minish->input[i] == '\"')
		{
			while (minish->input[++i] != '\"')
				if (minish->input[i] == ' ')
					minish->input[i] = minish->s;
		}
		else if (minish->input[i] == '\'')
		{
			while (minish->input[++i] != '\'')
				if (minish->input[i] == ' ')
					minish->input[i] = minish->s;
		}
		i++;
	}
}

void	post_split(t_minish *minish)
{
	int		i;

	if (minish->argv_list)
	{
		minish->skipper = minish->argv_list;
		minish->len = minish->argv_list->prev->id;
		while (minish->skipper && (minish->len)--)
		{
			if (minish->skipper->type)
			{
				if (ft_strcmp(minish->skipper->type, "ARG") == 0)
				{
					i = 0;
					while (minish->skipper->box[i++])
						if (minish->skipper->box[i] == minish->s)
							minish->skipper->box[i] = ' ';
				}
			}
			minish->skipper = minish->skipper->next;
		}
	}
}

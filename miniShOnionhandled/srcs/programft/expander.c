/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 01:13:06 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/14 05:13:49 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	env_to_search(t_minish *minish, int *i)
{
	char	*temp;
	int		k;

	k = ++(*i);
	while (minish->temporary[(*i)] && minish->temporary[(*i)] != '$'
		&& minish->temporary[(*i)] != ' ' && (minish->temporary[(*i)] != '\"'
			&& minish->temporary[(*i)] != '\''))
			(*i)++;
	minish->key = ft_substr(minish->temporary, k, (*i) - k);
	--(*i);
	if (src_in_list(&minish->env_list, minish->key))
	{
		temp = minish->key;
		freestr(minish->key);
		minish->key = ft_substr(minish->env_list->box,
				ft_strlen(minish->env_list->type) + 1,
				ft_strlen(minish->env_list->box));
	}
	k = -1;
	while (minish->key[++k])
		cpychar_gen(minish->key, k, &minish->input);
	freestr(minish->key);
}

void	double_quotes_handler(t_minish *minish, int *i)
{
	cpychar_gen(minish->temporary, *i, &minish->input);
	while (minish->temporary[++(*i)] != '\"')
	{
		if (double_env(minish, *i))
			(*i)++;
		else if (minish->temporary[*i] == '$'
			&& minish->temporary[*i + 1] != '$')
			env_to_search(minish, i);
		else if (minish->temporary[(*i)] == '\'')
			cpychar_gen(minish->temporary, *i, &minish->input);
		else
			cpychar_gen(minish->temporary, *i, &minish->input);
	}
	cpychar_gen(minish->temporary, *i, &minish->input);
}

void	single_quotes_handler(t_minish *minish, int *i)
{
	cpychar_gen(minish->temporary, *i, &minish->input);
	while (minish->temporary[++(*i)] != '\'')
	{
		if (double_env(minish, *i))
			(*i)++;
		else
			cpychar_gen(minish->temporary, *i, &minish->input);
	}
	cpychar_gen(minish->temporary, *i, &minish->input);
}

void	core_expander(t_minish *minish, int *i)
{
	if (minish->temporary[*i] == '\"')
		double_quotes_handler(minish, i);
	else if (minish->temporary[*i] == '\'')
		single_quotes_handler(minish, i);
	else if (double_env(minish, *i))
		(*i)++;
	else if (minish->temporary[*i] == '$'
		&& minish->temporary[*i + 1] != '$')
		env_to_search(minish, i);
	else
		cpychar_gen(minish->temporary, *i, &minish->input);
}

void	expander(t_minish *minish)
{
	int		i;

	i = -1;
	minish->input = calloc(sizeof(char), 1);
	while (minish->temporary[++i])
		core_expander(minish, &i);
	freestr(minish->temporary);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:50:39 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/14 05:21:05 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	doubles_count(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\"')
			i++;
		str++;
	}
	return (i);
}

int	single_count(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\'')
			i++;
		str++;
	}
	return (i);
}

void	sub_init_(t_minish *minish)
{
	minish->pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(minish->pwd, PATH_MAX);
	minish->cd_flag = 0;
	minish->input = readline(minish->name);
	minish->single_q = single_count(minish->input);
	minish->double_q = doubles_count(minish->input);
}

int	preliminary(t_minish *minish)
{
	if (minish->single_q == 1 || minish->double_q == 1)
	{
		add_history(minish->input);
		freestr(minish->input);
		return (1);
	}
	return (0);
}

int	get_input(t_minish *minish)
{
	char	*temp;
	int		i;

	temp = NULL;
	red();
	sub_init_(minish);
	if (preliminary(minish))
		return (0);
	add_history(minish->input);
	i = -1;
	while (minish->input[++i])
	{
		if (((minish->input[i] == '\"' && (minish->double_q % 2) == 0)
				|| (minish->input[i] == '\'' && minish->single_q % 2 == 0))
			|| (minish->single_q == 0 || minish->double_q == 0))
		{
			temp = ft_strtrim(minish->input, " ");
			minish->input = ft_strdup(temp);
			freestr(temp);
			white();
			return (1);
		}
	}
	white();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:50:39 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/25 08:56:40 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

int	doubles_count(char *str)
{
	int	i;
	int	in_singles;
	int	in_doubles;

	i = 0;
	in_singles = 0;
	in_doubles = 0;
	while (*str)
	{
		if (*str == '\'' && !in_doubles)
			in_singles = !in_singles;
		if (*str == '\"' && !in_singles)
		{
			i++;
			in_doubles = !in_doubles;
		}
			str++;
	}
	return (i);
}

int	single_count(char *str)
{
	int	i;
	int	in_singles;
	int	in_doubles;

	i = 0;
	in_doubles = 0;
	in_singles = 0;
	while (*str)
	{
		if (*str == '\"' && !in_singles)
			in_doubles = !in_doubles;
		if (*str == '\'' && !in_doubles)
		{
			i++;
			in_singles = !in_singles;
		}
		str++;
	}
	return (i);
}

void	sub_init_(t_minish *minish)
{
	minish->pwd = calloc(sizeof(char), PATH_MAX);
	getcwd(minish->pwd, PATH_MAX);
	minish->cd_flag = 0;
	minish->input = readline(minish->name);
	if (!minish->input)
		exit(0);
	minish->single_q = single_count(minish->input);
	minish->double_q = doubles_count(minish->input);
}

int	preliminary(t_minish *minish)
{
	if (minish->single_q % 2 == 1 || minish->double_q % 2 == 1)
	{
		add_history(minish->input);
		freestr(minish->input);
		write(2, "Invalid sintax\n", 16);
		return (1);
	}
	return (0);
}

int	get_input(t_minish *minish)
{
	char	*temp;
	int		i;

	red();
	sub_init_(minish);
	if (preliminary(minish))
		return (0);
	if (ft_strcmp(minish->input, ""))
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
	freestr(minish->pwd);
	return (0);
}

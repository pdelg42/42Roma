/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 07:13:25 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 16:05:33 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	case1(t_minish *minish)
{
	freestr(minish->env_list->box);
	freestr(minish->env_list->type);
	del_h(&minish->env_list);
	relister(&minish->env_list);
	minish->temporary = ft_strjoin(ft_strdup(minish->key), "=");
	if (minish->value)
		minish->temporary = ft_strjoin(minish->temporary,
				minish->value);
	else
	{
		minish->temporary = ft_strjoin(minish->temporary, "\"");
		minish->temporary = ft_strjoin(minish->temporary, "\"");
	}
}

void	case2(t_minish *minish)
{
	char	*temp;
	int		i;
	int		f;

	i = -1;
	f = 0;
	while (minish->env_list->box[++i])
		if (minish->env_list->box[i] == '=')
			f = 1;
	if (f == 1)
	{
		minish->temporary = ft_substr(minish->env_list->box, 0,
				ft_strlen(minish->env_list->box) - 1);
		temp = ft_substr(minish->value, 1, ft_strlen(minish->value));
		minish->temporary = ft_strjoin(minish->temporary, temp);
		freestr(minish->env_list->type);
		freestr(minish->env_list->box);
		freestr(temp);
		del_h(&minish->env_list);
	}
	else
		case_sub2(minish);
}

void	get_value(t_minish *minish, char *box)
{
	char	*c;
	int		i;

	i = 0;
	c = NULL;
	while (box[i] != '=')
		i++;
	if (box[++i])
	{
		if (box[i] != '\"')
		{
			c = calloc(sizeof(char), 2);
			c[0] = '\"';
			c[1] = 0;
			minish->temporary = ft_substr(box, i, ft_strlen(box));
			minish->value = ft_strjoin(c, minish->temporary);
			minish->value = ft_strjoin(minish->value, "\"");
			freestr(minish->temporary);
		}
		else
			minish->value = ft_substr(box, i, ft_strlen(box));
	}
	else
		minish->value = NULL;
}

void	get_key(t_minish *minish, int f)
{
	minish->temporary = key_fetcher(minish->skipper->box);
	if (f == 1 || f == 3)
		minish->key = ft_substr(minish->temporary, 0,
				ft_strlen(minish->temporary) - 1);
	else
		minish->key = ft_strdup(minish->temporary);
	freestr(minish->temporary);
}

int	get_flag(char *box, int *f)
{
	int	i;

	i = 0;
	while (box[i] && box[i] != '=')
	{
		if ((!ft_isalpha(box[i]) && !ft_isdigit(box[i]) && box[i] != '+'
				&& box[i] != '\\' && box[i] != '>' && box[i] != '<')
			|| (box[i] == '+' && box[i + 1] == '+')
			|| (box[i] == '\\' && box[i + 1] == '\\'))
		{
			printf("%s: %s: %s: not a valid identifier\n",
				">>> ", "export", box);
			return (0);
		}
		if (box[i] == '+' && box[i + 1] == '=')
			*f = 1;
		if (box[i + 1] == '=' && box[i] != '+' && box[i] != '\\')
			*f = 2;
		if (box[i] == '\\' && box[i + 1] == '=')
			*f = 3;
		if (box[i + 1] == '=' && box[i] != '+' && box[i] != '\\' && box[i + 1])
			*f = 4;
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:33:20 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/14 05:21:41 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	quotes_skipper(t_minish *minish, int *i)
{
	if (minish->input[(*i)] == '\"' || minish->input[(*i)] == '\'')
	{
		cpychar(minish, (*i)++);
		while (minish->input[(*i)] != '\"' && minish->input[(*i)] != '\''
			&& minish->input[*i])
			cpychar(minish, (*i)++);
	}
}

void	append_doc_adjust(t_minish *minish, int *i)
{
	if (minish->input[(*i) - 1] != ' ')
	{
		minish->temporary = ft_strjoin(minish->temporary, " ");
		cpychar(minish, (*i));
		cpychar(minish, (*i));
		(*i)++;
		minish->temporary = ft_strjoin(minish->temporary, " ");
	}
	else
	{	
		cpychar((minish), (*i));
		cpychar((minish), (*i)++);
		minish->temporary = ft_strjoin(minish->temporary, " ");
	}
}

void	single_adjust(t_minish *minish, int i)
{
	if ((i - 1) >= 0 && minish->input[i - 1] != ' ')
	{
		minish->temporary = ft_strjoin(minish->temporary, " ");
		cpychar(minish, i);
		if (minish->input[i + 1] != ' ')
			minish->temporary = ft_strjoin(minish->temporary, " ");
	}
	else if (minish->input[i + 1] && minish->input[i + 1] != ' ')
	{
		cpychar(minish, i);
		minish->temporary = ft_strjoin(minish->temporary, " ");
	}
	else
		cpychar((minish), i);
}

int	hard_checks(t_minish *minish, int i)
{
	if ((minish->input[i] == '>' && minish->input[i + 1] != '>'
			&& minish->input[i - 1] != ' ' && minish->input[i - 1] != '>')
		|| (minish->input[i] == '>' && minish->input[i + 1] != '>'
			&& minish->input[i - 1] == ' ' && minish->input[i - 1] != '>')
		|| (minish->input[i] == '<' && minish->input[i + 1] != '<'
			&& minish->input[i - 1] != ' ' && minish->input[i - 1] != '<')
		|| (minish->input[i] == '<' && minish->input[i + 1] != '<'
			&& minish->input[i - 1] == ' ' && minish->input[i - 1] != '<')
		|| (minish->input[i] == '|'))
		return (1);
	return (0);
}		

void	input_handler(t_minish *minish)
{
	int		i;

	i = 0;
	(minish)->temporary = calloc(sizeof(char), 1);
	while ((minish)->input[i])
	{
		quotes_skipper(minish, &i);
		if (((minish)->input[i] == '<' || (minish)->input[i] == '>') && i == 0
			&& ((minish)->input[i + 1] != '>' && (minish)->input[i + 1] != '<'
				&& (minish)->input[i] == ' '))
		{
			cpychar((minish), i);
			minish->temporary = ft_strjoin(minish->temporary, " ");
		}
		else if (hard_checks(minish, i))
			single_adjust((minish), i);
		else if (((minish)->input[i] == '>' && (minish)->input[i + 1] == '>')
			|| ((minish)->input[i] == '<' && (minish)->input[i + 1] == '<'))
			append_doc_adjust((minish), &i);
		else
			cpychar((minish), i);
		i++;
	}
	freestr(minish->input);
}

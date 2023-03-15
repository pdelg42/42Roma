/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tagger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:28:53 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/11 15:53:58 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	update_conditions(t_node *tmp, int *cmd_flag)
{
	if (redir_compare(tmp->box))
		tmp->type = "REDIR";
	else if (append_compare(tmp->box))
		tmp->type = "APPEND";
	else if (heredoc_compare(tmp->box))
		tmp->type = "HEREDOC";
	else
	{
		*cmd_flag = 1;
		tmp->type = "CMD";
	}
}

void	absolute_update(t_node *tmp, int len)
{
	while (tmp && len--)
	{
		if (ft_strcmp(tmp->type, "CMD") == 0)
		{
			if (tmp->box[0] == '/')
				tmp->status |= 1;
			else if (tmp->box[0] == '.')
				tmp->status |= 2;
			else if (builtin_compare(tmp->box))
				tmp->type = "BUILT";
		}
		tmp = tmp->next;
	}
}

void	setup(t_node *tmp, int len)
{
	while (tmp && len--)
	{
		if (redir_compare(tmp->box) || append_compare(tmp->box))
		{
			if (redir_compare(tmp->box))
				tmp->type = "REDIR";
			else
				tmp->type = "APPEND";
			tmp = tmp->next;
			tmp->type = "FILE";
		}
		else if (heredoc_compare(tmp->box))
		{
			tmp->type = "HEREDOC";
			if (tmp->next->id != 1)
				tmp->next->type = "EOF";
			tmp = tmp->next;
		}
		else if (ft_strcmp(tmp->box, "|") == 0)
			tmp->type = "PIPE";
		else
			tmp->type = "ARG";
		tmp = tmp->next;
	}
}

void	update(t_node *tmp, int len)
{
	int	cmd_flag;

	cmd_flag = 0;
	while (tmp && len--)
	{
		if (tmp->id == 1)
			update_conditions(tmp, &cmd_flag);
		else if (ft_strcmp(tmp->type, "PIPE") == 0)
		{
			tmp = tmp->next;
			cmd_flag = 0;
			update_conditions(tmp, &cmd_flag);
		}
		else if (!ft_strcmp(tmp->type, "FILE")
			&& !ft_strcmp(tmp->next->type, "ARG")
			&& !cmd_flag)
		{
			tmp = tmp->next;
			cmd_flag = 1;
			tmp->type = "CMD";
		}
		tmp = tmp->next;
	}
}

void	tagger(t_minish *minish)
{
	if (minish->argv_list)
	{
		minish->skipper = minish->argv_list;
		minish->len = minish->argv_list->prev->id;
		setup(minish->skipper, minish->len);
		update(minish->skipper, minish->len);
		absolute_update(minish->skipper, minish->len);
	}
}

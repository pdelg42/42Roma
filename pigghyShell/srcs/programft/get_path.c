/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:28:04 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 15:58:30 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	cmd_adjust(t_minish *minish)
{
	char	*temp;
	int		dist;

	dist = get_dist_from_anchor(minish->argv_list);
	if (minish->argv_list->box[0] == '\"'
		|| minish->argv_list->box[ft_strlen(minish->argv_list->box)]
		== '\"')
	{
		temp = ft_strtrim(minish->argv_list->box, "\"");
		freestr(minish->ft_argv[dist]);
		minish->ft_argv[dist] = ft_strdup(temp);
		minish->argv_list->box = ft_strdup(temp);
		freestr(temp);
	}
}

int	command_not_found(DIR *dp, t_minish *minish)
{
	int	dist;

	dist = get_dist_from_anchor(minish->argv_list);
	if (dp == NULL)
	{
		fprintf(stderr, ">>>: %s: command not found\n", minish->ft_argv[dist]);
		return (1);
	}
	return (0);
}

int	sub_seeker(struct dirent *entry, t_minish *minish, DIR *dp, t_node *tmp)
{
	t_node	*cmd_p;
	char	*semipath;

	if (minish->argv_list)
		cmd_adjust(minish);
	cmd_p = minish->argv_list;
	list_point_to(&minish->argv_list, 1);
	if (cmd_p)
	{
		while (entry)
		{
			if (!ft_strcmp(entry->d_name,
					minish->ft_argv[get_dist_from_anchor(cmd_p)]))
			{
				semipath = ft_strjoin(ft_strdup(tmp->box), "/");
				minish->cmd = ft_strjoin(semipath,
						minish->ft_argv[get_dist_from_anchor(cmd_p)]);
				closedir(dp);
				return (1);
			}
			else
				entry = readdir(dp);
		}
	}
	return (0);
}

int	seeker(t_minish *minish)
{
	DIR				*dp;
	struct dirent	*entry;

	minish->skipper = minish->paths_list;
	minish->len = len_list(&minish->paths_list);
	while (minish->skipper && (minish->len)--)
	{
		dp = opendir(minish->skipper->box);
		if (command_not_found(dp, minish))
		{
			minish->cmd = NULL;
			return (1);
		}
		entry = readdir(dp);
		if (sub_seeker(entry, minish, dp, minish->skipper))
			return (0);
		closedir(dp);
		minish->skipper = minish->skipper->next;
	}
	if (checks0(minish))
		return (1);
	return (0);
}

void	get_paths(t_minish	*minish)
{
	int		i;

	minish->temp = ft_split(get_env(minish, "PATH"), ':');
	freestr(minish->temporary);
	i = -1;
	while (minish->temp[++i])
		add_t(&minish->paths_list, new_(minish->temp[i], 0));
	freematrix(minish->temp, row_counter(minish->temp));
	relister(&minish->paths_list);
	seeker(minish);
	freenode(minish->paths_list);
	freelist(&minish->paths_list);
}

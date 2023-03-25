/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 05:40:11 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 06:54:55 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

void	cd_sub(t_minish *minish)
{
	minish->pwd = calloc(sizeof(char), PATH_MAX);
	getcwd(minish->pwd, PATH_MAX);
	src_in_list(&minish->env_list, "PWD");
	freestr(minish->env_list->box);
	minish->env_list->box = ft_strjoin(ft_strdup("PWD="), minish->pwd);
	freestr(minish->pwd);
}

int	cd_b(t_minish *minish)
{
	minish->cd_flag = 1;
	if (minish->argv_list->prev->id == 1)
		return (1);
	if (chdir(minish->argv_list->next->box) == -1)
	{
		perror(minish->argv_list->next->box);
		return (1);
	}
	src_in_list(&minish->env_list, "OLDPWD");
	freestr(minish->env_list->box);
	freestr(minish->env_list->type);
	del_h(&minish->env_list);
	relister(&minish->env_list);
	minish->temporary = calloc(sizeof(char), 1);
	minish->temporary = ft_strjoin(minish->temporary, "OLDPWD=");
	minish->temporary = ft_strjoin(minish->temporary, minish->pwd);
	add_t(&minish->env_list,
		new_(minish->temporary, minish->env_list->prev->id + 1));
	freestr(minish->temporary);
	freestr(minish->pwd);
	cd_sub(minish);
	return (1);
}

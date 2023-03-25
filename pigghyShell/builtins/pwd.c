/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:30:40 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/24 06:57:02 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/program.h"

int	main(int ac, char **av, char **env)
{
	char	*pwd;

	pwd = getenv("PWD");
	printf("%s\n", pwd);
	return (0);
}

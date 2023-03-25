/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:25:51 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/24 15:59:26 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	print(char **argv, int do_nl)
{
	int		i;
	char	*tmp;

	tmp = calloc(sizeof(char), 1);
	while (*argv)
	{
		tmp = ft_strjoin(tmp, *argv++);
		tmp = ft_strjoin(tmp, " ");
	}
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] == '\"')
			while (tmp[i + 1] != 0 && tmp[++i] != '\"')
				write(1, &tmp[i], 1);
		else if (tmp[i] == '\'')
			while (tmp[i + 1] != 0 && tmp[++i] != '\'')
				write(1, &tmp[i], 1);
		else
			write(1, &tmp[i], 1);
	}
	if (do_nl)
		write(1, "\n", 1);
	freestr(tmp);
}

int	check_nl(char **argv)
{
	int	i;

	i = 0;
	if ((*argv)[i++] != '-')
		return (1);
	while ((*argv)[i])
		if ((*argv)[i] && (*argv)[i++] != 'n')
			return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	nl;
	int	i;

	if (ac == 1)
		return (write(1, "\n", 1) - 1);
	nl = check_nl(++av);
	i = nl;
	while (av && !i)
		i = check_nl(++av);
	if (i && av)
		print(av, nl);
	return (0);
}

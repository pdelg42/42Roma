/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:25:51 by gdel-giu          #+#    #+#             */
/*   Updated: 2023/03/14 04:54:14 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	print(char *temp, char **argv)
{
	int		i;

	temp = calloc(sizeof(char), 1);
	while (*argv)
	{
		temp = ft_strjoin(temp, *argv++);
		temp = ft_strjoin(temp, " ");
	}
	i = -1;
	while (temp[++i])
	{
		if (temp[i] == '\"')
			while (temp[++i] != '\"')
				write(1, &temp[i], 1);
		else if (temp[i] == '\'')
			while (temp[++i] != '\'')
				write(1, &temp[i], 1);
		else
			write(1, &temp[i], 1);
	}
	free (temp);
	temp = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while ((*s1 && *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (*str)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*sum;

	sum = malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!sum)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		sum[i++] = s1[j++];
	j = 0;
	while (s2[j])
		sum[i++] = s2[j++];
	sum[i] = '\0';
	free((char *)s1);
	return (sum);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		f;
	int		rows;
	char	*temp;

	i = 0;
	rows = 0;
	while (argv[i++])
		rows++;
	if (rows == 1)
	{
		printf("\n");
		return (0);
	}
	argv++;
	i = 0;
	if (ft_strcmp(argv[i++], "-n") == 0)
	{
		f = 1;
		argv++;
	}
	print(temp, argv);
	if (f != 1)
		printf("\n");
	return (0);
}

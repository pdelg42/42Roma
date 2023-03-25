/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdel-giu <gdel-giu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:13:59 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/22 15:35:48 by gdel-giu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/program.h"

static int	ft_inset(int c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	s;
	size_t	e;
	char	*str;

	s = 0;
	while (s1[s] && ft_inset(s1[s], set))
			s++;
	e = ft_strlen(s1);
	while (e > s && ft_inset(s1[e - 1], set))
		e--;
	str = (char *) calloc(sizeof(*s1), (e - s + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s < e)
		str[i++] = s1[s++];
	str[i] = 0;
	free((char *)s1);
	s1 = NULL;
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:30:19 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/14 05:05:06 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/program.h"

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	substr = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			substr[j] = s[i];
			j++;
		}
		i++;
	}
	substr[j] = '\0';
	return (substr);
}

char	*get_env_value(char *box)
{
	char	*value;
	int		i;

	i = 0;
	while (box[i] != '=')
		i++;
	if (box[++i])
		value = ft_substr(box, i, ft_strlen(box));
	else
		value = NULL;
	return (value);
}

int	main(int argc, char **argv, char **env)
{
	char	*temp;
	char	*value;

	while (*env)
	{
		temp = *env++;
		value = get_env_value(temp);
		if (value)
		{
			printf("%s\n", temp);
			free (value);
			value = NULL;
		}
	}
	return (0);
}

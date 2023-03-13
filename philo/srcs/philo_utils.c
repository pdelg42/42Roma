/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:12:41 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/09 12:27:51 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(long long time)
{
	long long	tmp;

	tmp = ft_time();
	usleep(time * 1000 - 20000);
	while (ft_time() < tmp + time)
		continue ;
}

void	starvin_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->params->philo_time);
	ph->starvin = ft_time() - ph->params->start_program;
	pthread_mutex_unlock(&ph->params->philo_time);
}

int	check_mutex(t_philo *ph, int flag)
{
	int	i;

	i = 0;
	if (flag == 0)
	{
		pthread_mutex_lock(&ph->params->death);
		i = ph->params->is_death;
		pthread_mutex_unlock(&ph->params->death);
	}
	if (flag == 1)
	{
		pthread_mutex_lock(&ph->params->must_eat_thread);
		i = ph->end;
		pthread_mutex_unlock(&ph->params->must_eat_thread);
	}
	return (i);
}

void	message(t_philo *ph, char *sms)
{
	pthread_mutex_lock(&ph->params->printing);
	printf("%lld %d %s", ft_time() - ph->params->start_program, ph->id, sms);
	pthread_mutex_unlock(&ph->params->printing);
}

void	ft_monitoring(t_input *input)
{
	while (1)
	{
		if (ft_finish(input) || !check_mutex(input->philo, 0))
			break ;
	}
}

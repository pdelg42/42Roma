/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:08:44 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/13 23:15:50 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_print(void *ph, char *sms)
{
	if (check_mutex(ph, 0))
		message(ph, sms);
}

void	*handler_philo(void *philo)
{
	t_philo	*ph;

	ph = philo;
	starvin_time(ph);
	if (ph->id % 2 == 0)
		ft_sleep(ph->params->eat_time);
	while (check_mutex(ph, 0))
	{
		pthread_mutex_lock(ph->next);
		check_print(ph, "has taken a fork\n");
		if (ph->params->n_philos == 1)
			break ;
		pthread_mutex_lock(ph->prev);
		check_print(ph, "is eating\n");
		ph->meals++;
		if (ph->meals == ph->params->must_eat)
		{
			pthread_mutex_lock(&ph->params->must_eat_thread);
			ph->end = 0;
			pthread_mutex_unlock(&ph->params->must_eat_thread);
		}
		utils(&ph);
	}
	return (NULL);
}

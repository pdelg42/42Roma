/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:53:14 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/13 23:05:22 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	utils(t_philo **ph)
{
	starvin_time(*ph);
	ft_sleep((*ph)->params->eat_time);
	pthread_mutex_unlock((*ph)->next);
	pthread_mutex_unlock((*ph)->prev);
	if (check_mutex((*ph), 0))
		message((*ph), "is sleeping\n");
	ft_sleep((*ph)->params->sleep_time);
	if (check_mutex(*ph, 0))
		message(*ph, "is thinking\n");
}

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	destroyer(t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->n_philos)
		pthread_mutex_destroy(&input->forks[i]);
	pthread_mutex_destroy(&input->death);
	pthread_mutex_destroy(&input->must_eat_thread);
	pthread_mutex_destroy(&input->philo_time);
	pthread_mutex_destroy(&input->printing);
	free(input->philo);
	free(input->forks);
}

void	init_mutex(t_philo *philo)
{
	pthread_mutex_init(&philo->params->death, NULL);
	pthread_mutex_init(&philo->params->must_eat_thread, NULL);
	pthread_mutex_init(&philo->params->philo_time, NULL);
	pthread_mutex_init(&philo->params->printing, NULL);
}

void	init_params(t_input *input, char **argv)
{
	int	i;

	i = -1;
	input->n_philos = _a(argv[1], 10);
	input->death_time = _a(argv[2], 10);
	input->eat_time = _a(argv[3], 10);
	input->sleep_time = _a(argv[4], 10);
	input->must_eat = _a(argv[5], 10);
	input->is_death = 1;
	input->philo = malloc(sizeof(t_philo) * input->n_philos);
	input->forks = malloc(sizeof(pthread_mutex_t) * input->n_philos);
	while (++i < input->n_philos)
		pthread_mutex_init(&input->forks[i], NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 08:54:33 by aperrone          #+#    #+#             */
/*   Updated: 2023/03/13 23:10:25 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_finish_sub(long long time, t_input *input, int i)
{
	if (time > input->death_time)
	{
		pthread_mutex_lock(&input->death);
		input->is_death = 0;
		pthread_mutex_unlock(&input->death);
		usleep(200);
		message(&input->philo[i], "died\n");
		return (1);
	}
	return (0);
}

void	init_philo(t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->n_philos)
	{
		input->philo[i].id = i;
		input->philo[i].end = 1;
		input->philo[i].meals = 0;
		input->philo[i].prev = &input->forks[i];
		if (i == input->n_philos)
			input->philo[i].next = &input->forks[0];
		else
			input->philo[i].next = &input->forks[i + 1];
		input->philo[i].params = input;
	}
}

int	main(int argc, char **argv)
{
	t_input		input;
	int			i;
	int			n;

	n = argc;
	init_params(&input, argv);
	init_philo(&input);
	init_mutex(input.philo);
	i = -1;
	input.start_program = ft_time();
	while (++i < input.n_philos)
		pthread_create(&input.philo[i].thread, NULL,
			handler_philo, &input.philo[i]);
	ft_monitoring(&input);
	i = -1;
	while (++i < input.n_philos)
		pthread_join(input.philo[i].thread, NULL);
	destroyer(&input);
	return (0);
}

int	ft_finish(t_input *input)
{
	int			i;
	int			f;
	long long	time;

	i = -1;
	f = 0;
	while (++i < input->n_philos)
	{
		pthread_mutex_lock(&input->philo_time);
		time = ft_time() - input->start_program - input->philo[i].starvin;
		pthread_mutex_unlock(&input->philo_time);
		if (ft_finish_sub(time, input, i))
			return (1);
		if (!check_mutex(&input->philo[i], 1))
			f++;
	}
	if (f == input->n_philos)
	{
		pthread_mutex_lock(&input->death);
		input->is_death = 0;
		pthread_mutex_unlock(&input->death);
	}
	return (0);
}

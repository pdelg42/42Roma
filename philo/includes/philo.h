/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperrone <aperrone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:46:26 by aperrone          #+#    #+#             */
/*   Updated: 2023/01/04 12:29:19 by aperrone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				end;
	int				meals;
	long long int	starvin;
	pthread_mutex_t	*next;
	pthread_mutex_t	*prev;
	pthread_t		thread;
	struct s_input	*params;
}	t_philo;

typedef struct s_input
{
	int				n_philos;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				is_death;
	long long int	start_program;
	pthread_mutex_t	death;
	pthread_mutex_t	must_eat_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	philo_time;
	pthread_mutex_t	printing;
	struct s_philo	*philo;
}	t_input;

long long	_a(char *str, int len_base);
void		*handler_philo(void *philo);
long long	ft_time(void);
void		ft_sleep(long long time);
void		starvin_time(t_philo *philo);
int			check_mutex(t_philo *ph, int flag);
void		message(t_philo *ph, char *sms);
void		ft_monitoring(t_input *input);
int			ft_finish(t_input *input);
void		init_params(t_input *input, char **argv);
void		init_mutex(t_philo *philo);
void		destroyer(t_input *input);
int			ft_finish_sub(long long time, t_input *input, int i);
void		utils(t_philo **ph);
void		*handler_philo(void *philo);
#endif
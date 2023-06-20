/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaplin <ktaplin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:19:50 by ktaplin           #+#    #+#             */
/*   Updated: 2023/06/20 14:16:43 by ktaplin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_number	*number, int id, char *s)
{
	if (number->died != 1 && number->all_ate != 1)
	{
		printf("%lli %d %s", (timestamp() - number->first_timestamp), id, s);
	}
}

void	ft_eat_time(long long time, t_number	*number)
{
	long long	past;

	past = timestamp();
	while (number->died != 1)
	{
		if (timestamp() - past >= time)
			break ;
		usleep(time / 10);
	}
}

void	ft_eat(t_philosopher *philo)
{
	t_number	*number;

	number = philo->number;
	pthread_mutex_lock(&(number->fork_id[philo->left_fork_id]));
	pthread_mutex_lock(&(number->writing));
	ft_print(number, philo->id, " has taken a fork\n");
	pthread_mutex_unlock(&(number->writing));
	pthread_mutex_lock(&(number->fork_id[philo->right_fork_id]));
	pthread_mutex_lock(&(number->writing));
	ft_print(number, philo->id, " has taken a fork\n");
	pthread_mutex_unlock(&(number->writing));
	pthread_mutex_lock(&(number->meal_check));
	pthread_mutex_lock(&(number->writing));
	ft_print(number, philo->id, " is eating\n");
	pthread_mutex_unlock(&(number->writing));
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(number->meal_check));
	ft_eat_time(number->time_to_eat, number);
	if (number->n_time_to_eat != -1)
		philo->n_meal++;
	pthread_mutex_unlock(&(number->fork_id[philo->left_fork_id]));
	pthread_mutex_unlock(&(number->fork_id[philo->right_fork_id]));
}

void	ft_sleep(long long time, t_number	*number)
{
	long long	past;

	past = timestamp();
	while (number->died != 1)
	{
		if (timestamp() - past >= time)
			break ;
		usleep(time / 10);
	}
}

void	launch(t_number	*number)
{
	int				i;
	t_philosopher	*philo;

	i = 1;
	number->first_timestamp = timestamp();
	philo = number->philosophers;
	while (i <= number->n_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL,
				philo_life, &(philo[i])) != 0)
			error(2);
		i++;
	}
	death(number, number->philosophers);
	destroy(number, philo);
}

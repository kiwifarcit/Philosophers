/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaplin <ktaplin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:36:38 by ktaplin           #+#    #+#             */
/*   Updated: 2023/06/20 14:36:25 by ktaplin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_number *number, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (++i <= number->n_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = 0;
	while (++i <= number->n_philo)
		pthread_mutex_destroy(&(number->fork_id[i]));
	pthread_mutex_unlock(&(number->writing));
	pthread_mutex_destroy(&(number->writing));
	pthread_mutex_destroy(&(number->meal_check));
}

void	*philo_life(void *void_philosopher)
{
	t_philosopher	*philo;
	t_number		*number;

	philo = (t_philosopher *)void_philosopher;
	number = philo->number;
	if (philo->id % 2 == 0)
		usleep(300);
	while (number->died == 0)
	{
		ft_eat(philo);
		if (number->all_ate != 0)
			break ;
		pthread_mutex_lock(&(number->writing));
		ft_print(number, philo->id, " is sleeping\n");
		pthread_mutex_unlock(&(number->writing));
		ft_sleep(number->time_to_sleep, number);
		pthread_mutex_lock(&(number->writing));
		ft_print(number, philo->id, " is thinking\n");
		pthread_mutex_unlock(&(number->writing));
	}
	return (0);
}

void	all_ate_check(t_number	*number)
{
	if (number->meal == number->n_philo && number->n_time_to_eat != -1)
		number->all_ate = 1;
	number->meal = 1;
}

void	death(t_number *number, t_philosopher *philo)
{
	int			i;
	long long	time;

	i = 1;
	while (number->all_ate == 0)
	{
		if (i >= number->n_philo)
		{	
			all_ate_check(number);
			i = 1;
		}
		time = timestamp();
		if (time - philo[i].last_meal > number->time_to_die)
		{
			ft_print(number, i, " died\n");
			number->died = 1;
		}
		if (philo[i].n_meal >= number->n_time_to_eat)
			number->meal++;
		if (number->died == 1)
			break ;
		i++;
		usleep(100);
	}
}

int	main(int argc, char	**argv)
{
	t_number	number;

	if (argc != 5 && argc != 6)
		error(0);
	if ((argv))
		init(argv, &number);
	exit(EXIT_SUCCESS);
}

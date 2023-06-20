/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaplin <ktaplin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:12:57 by ktaplin           #+#    #+#             */
/*   Updated: 2023/06/20 14:34:27 by ktaplin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	one_philo(t_number	*number)
{
	long long	past;
	long long	time;

	time = number->time_to_die;
	past = timestamp();
	printf("0 1 has taken a fork\n");
	while (number->died != 1)
	{
		if (timestamp() - past >= time)
			break ;
	}
	printf("%d 1 died\n", number->time_to_die);
	number->died = 1;
}

void	init_mutex(t_number	*number)
{
	int	i;

	i = 0;
	number->fork_id = malloc(sizeof(pthread_mutex_t) * number->n_philo);
	while (i < number->n_philo)
	{
		if (pthread_mutex_init(&(number->fork_id[++i]), NULL) != 0)
			error(2);
	}
	if (pthread_mutex_init(&(number->writing), NULL) != 0)
		error(2);
	if (pthread_mutex_init(&(number->meal_check), NULL) != 0)
		error(2);
}

void	init_philo(t_number	*number)
{
	int	i;

	number->philosophers = malloc(sizeof(number->philosophers)
			* number->n_philo);
	i = 1;
	while (i < number->n_philo)
	{
		number->philosophers[i].id = i;
		number->philosophers[i].left_fork_id = i;
		number->philosophers[i].right_fork_id = i + 1;
		number->philosophers[i].last_meal = timestamp();
		number->philosophers[i].n_meal = 0;
		number->philosophers[i].number = number;
		i++;
	}
	number->philosophers[i].id = i;
	number->philosophers[i].left_fork_id = i;
	number->philosophers[i].right_fork_id = 1;
	number->philosophers[i].last_meal = timestamp();
	number->philosophers[i].n_meal = 0;
	number->philosophers[i].number = number;
}

void	init(char	**argv, t_number	*number)
{
	number->n_philo = ft_atoi(argv[1]);
	number->time_to_die = ft_atoi(argv[2]);
	number->time_to_eat = ft_atoi(argv[3]);
	number->time_to_sleep = ft_atoi(argv[4]);
	number->died = 0;
	number->all_ate = 0;
	number->meal = 1;
	if (argv[5])
		number->n_time_to_eat = ft_atoi(argv[5]);
	else
		number->n_time_to_eat = -1;
	if (number->n_philo <= 0 || number->time_to_die < 0
		|| number->time_to_eat < 0 || number->time_to_sleep < 0
		|| number->n_philo > 250)
		error(1);
	if (number->n_philo == 1)
		one_philo(number);
	init_mutex(number);
	init_philo(number);
	launch(number);
}

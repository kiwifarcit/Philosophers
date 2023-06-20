/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaplin <ktaplin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:30:52 by ktaplin           #+#    #+#             */
/*   Updated: 2023/06/20 14:20:12 by ktaplin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

struct	s_number;

typedef struct s_philosopher
{
	int					id;
	int					left_fork_id;
	int					right_fork_id;
	pthread_t			thread_id;
	long long			last_meal;
	int					n_meal;
	struct s_number		*number;

}	t_philosopher;

typedef struct s_number
{
	int					n_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_time_to_eat;
	int					died;
	int					all_ate;
	int					meal;
	long long			first_timestamp;
	t_philosopher		*philosophers;
	pthread_mutex_t		*fork_id;
	pthread_mutex_t		writing;
	pthread_mutex_t		meal_check;

}	t_number;

int			ft_atoi(const	char	*str);
void		ft_putstr_fd(char *s, int fd);
void		error(int i);
void		init_mutex(t_number	*number);
void		init_philo(t_number	*number);
void		init(char	**argv, t_number	*number);
long long	timestamp(void);
void		launch(t_number	*number);
void		ft_sleep(long long time, t_number	*number);
void		ft_eat(t_philosopher *philo);
void		ft_eat_time(long long time, t_number	*number);
void		ft_print(t_number	*number, int id, char *s);
void		launch(t_number	*number);
void		init(char	**argv, t_number	*number);
void		death(t_number *number, t_philosopher *philo);
void		*philo_life(void *void_philosopher);
void		destroy(t_number *number, t_philosopher *philo);

#endif
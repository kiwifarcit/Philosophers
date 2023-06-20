/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaplin <ktaplin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:44:30 by ktaplin           #+#    #+#             */
/*   Updated: 2023/06/20 14:32:18 by ktaplin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(int i)
{
	if (i == 0)
		ft_putstr_fd("Wrong Number Of Arguments\n", 2);
	if (i == 1)
		ft_putstr_fd("Wrong Values\n", 2);
	if (i == 2)
		ft_putstr_fd("Error While Creating Threads\n", 2);
	exit (EXIT_FAILURE);
}

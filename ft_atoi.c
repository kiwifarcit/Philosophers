/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaplin <ktaplin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:48:00 by ktaplin           #+#    #+#             */
/*   Updated: 2023/05/31 16:43:19 by ktaplin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c);
static int	int_(const char *str);

int	ft_atoi(const char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(*str))
		str++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			error(1);
		i++;
	}
	return (int_(str));
}

static int	int_(const char *str)
{		
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static int	ft_isspace(char c)
{
	return (c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ');
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

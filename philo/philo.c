/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:37:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/23 16:58:22 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"
#include <unistd.h>

//./philo time time time (optional) returns 1 for error

static void	bed(t_philo *philo)
{
	long long	dur;
	long long	curr;
	long long	start;

	start = your_time();
	death_check((philo), "is sleeping");
	while (1)
	{
		usleep(100);
		curr = your_time();
		dur = curr - start;
		if (dur >= philo->main_struct->time_to_sleep)
		{
			break ;
		}
	}
}

	// thread routine
	// pthread_detach(philo->thread);

void	sleepornot(t_philo *philo)
{
	if (philo->main_struct->philo_num % 2 == 1)
	{
		if (philo->id % 3 != 0)
			usleep(1000 * philo->main_struct->time_to_eat * \
			(philo->id % 3) - 10000);
	}
	else
	{
		if (philo->id % 2 == 0)
			usleep(1000 * philo->main_struct->time_to_eat - 10000);
	}
}

void	*routine(t_philo *philo)
{
	if ((philo->main_struct->philo_num) != 1)
		sleepornot(philo);
	pthread_mutex_lock(&(philo->main_struct->last_meal));
	philo->lastmeal = your_time();
	pthread_mutex_unlock(&(philo->main_struct->last_meal));
	while (17 && (philo->main_struct->philo_num) != 1)
	{
		pthread_mutex_lock(&(philo->main_struct->death));
		if (philo->main_struct->dead)
		{
			pthread_mutex_unlock(&(philo->main_struct->death));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->main_struct->death));
		eat(philo);
		if (philo->full == philo->main_struct->meal_amount)
			break ;
		bed(philo);
		death_check(philo, "is thinking");
	}
	return (NULL);
}

static int	init_philo(t_struct *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		info->philos[i].main_struct = info;
		info->philos[i].id = i + 1;
		info->philos[i].left_fork = &info->fork[i];
		info->philos[i].right_fork = &info->fork[(i + 1) % info->philo_num];
		info->philos[i].lastmeal = your_time();
		info->philos[i].full = 0;
		i++;
	}
	info->fullaf = 0;
	info->dead = 0;
	return (0);
}

int	parse_info(t_struct *info)
{
	info->philos = malloc(info->philo_num * sizeof(t_philo));
	info->fork = malloc(info->philo_num * sizeof(pthread_mutex_t));
	if (!info->philos || !info->fork)
		return (1);
	if (create_mutex(info))
		ft_puterror("Failed to create mutexes");
	init_philo(info);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:37:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 17:19:47 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"
#include <unistd.h>

//./philo time time time (optional) returns 1 for error

void	*routine(t_philo *philo)
{
	philo->lastmeal = your_time();
	pthread_mutex_lock(&philo->main_struct->print);
	printf("last meal:%llu\n", philo -> lastmeal);
	pthread_mutex_unlock(&philo->main_struct->print);
	if (philo->id % 2 == 0)
		usleep(42);
	return (NULL);
}

int	create_mutex(t_struct *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&info->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->death, NULL) != 0)
		return (1);
	return (0);
}

int	init_philo(t_struct *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		info->philos[i].main_struct = info;
		info->philos[i].id = i + 1;
		info->philos[i].left_fork = &info->fork[i];
		info->philos[i].right_fork = &info->fork[(i + 1) % info->philo_num];
		i++;
	}
	info->dead = 0;
	return (0);
}

int	parse_info(t_struct *info)
{
	int	i;

	i = 0;
	info->philos = malloc(info->philo_num * sizeof(t_philo));
	info->fork = malloc(info->philo_num * sizeof(pthread_mutex_t));
	if (!info->philos || !info->fork)
		return (1);
	ft_putendl("Malloc done");
	init_philo(info);
	return (0);
}

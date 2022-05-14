/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:37:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/14 21:02:44 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"
#include <unistd.h>

//./philo time time time (optional) returns 1 for error

void	bed(t_philo *philo)
{
	long long	dur;
	long long	curr;
	long long	start;
	start = your_time();
	death_check((philo),"is sleeping");
	while(1)
	{
		usleep(100);
		curr = your_time();
		dur = curr - start;
		if(dur >= philo->main_struct->time_to_sleep)
		{
			break ;
		}
	}
}

// idk what this function do pls help me
void	*routine(t_philo *philo)
{
	pthread_detach(philo->thread);
	philo->lastmeal = your_time();
	if (philo->id % 2 == 0)
		usleep(42);
	while(17)
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
	if (create_mutex(info)) //create mutex before initiating them
		ft_puterror("Failed to create mutexes");
	//ft_putendl("Malloc done");
	init_philo(info);
	return (0);
}

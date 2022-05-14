/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:37:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/14 18:10:37 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"
#include <unistd.h>
void	youdedbruh(t_philo *philo, long long curr)
{
	pthread_mutex_lock(&(philo->main_struct->death));
	philo->main_struct->dead = 1;
	pthread_mutex_unlock(&(philo->main_struct->death));
	pthread_mutex_lock(&philo->main_struct->print);//
	printf("時間%llu二：ここに死んでいました\n", curr);
	pthread_mutex_unlock(&philo->main_struct->print);//
}
//./philo time time time (optional) returns 1 for error

void	bed(t_philo *philo)
{
	long long	dur;
	long long	curr;
	long long	start;
	start = your_time();
	pthread_mutex_lock(&(philo->main_struct->death));
	if (philo->main_struct->dead)
	return ;
	pthread_mutex_unlock(&(philo->main_struct->death));
	pthread_mutex_lock(&philo->main_struct->print);//
	printf("%05llu %d is sleeping\n", your_time() - philo->main_struct->p_start_time, philo->id);
		pthread_mutex_unlock(&philo->main_struct->print);//
	while(1)
	{
		usleep(100);
		curr = your_time();
		dur = curr - start;
		if (curr - philo->lastmeal >= philo->main_struct->time_to_eat)
		{
			youdedbruh(philo, curr);
			break ;
		}
		pthread_mutex_lock(&philo->main_struct->death);
		if((dur >= philo->main_struct->time_to_sleep) && (!philo->main_struct->dead))
		{
			pthread_mutex_unlock(&philo->main_struct->death);
			break ;
		}
		pthread_mutex_unlock(&philo->main_struct->death);
	}
}

// idk what this function do pls help me
void	*routine(t_philo *philo)
{
	philo->lastmeal = your_time();
	long long	c_time;
	if (philo->id % 2 == 0)
		usleep(42);
	while(1)
	{
		c_time = your_time();
		int ima = c_time - philo->lastmeal; // how long hasnt eaten since lastmeal?
		if (ima >= philo->main_struct->time_to_eat)
		{
			youdedbruh(philo, c_time);
			break ;
		}
		else
		{
		if (eat(philo))
		{
			break;
		}
		if (philo->full == philo->main_struct->meal_amount)
			break;
		pthread_mutex_lock(&(philo->main_struct->death));
		if (philo->main_struct->dead)
		{
		pthread_mutex_unlock(&(philo->main_struct->death));
		break;
		}
		pthread_mutex_unlock(&(philo->main_struct->death));
		bed(philo);
		pthread_mutex_lock(&(philo->main_struct->death));
		if (philo->main_struct->dead)
		{
		pthread_mutex_unlock(&(philo->main_struct->death));
		break;
		}
		pthread_mutex_unlock(&(philo->main_struct->death));
		pthread_mutex_lock(&philo->main_struct->print);//
		printf("%05llu %d is thinking\n", (your_time() - philo->main_struct->p_start_time), philo->id);
		pthread_mutex_unlock(&philo->main_struct->print);//
		}
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

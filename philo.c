/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:37:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 20:56:35 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"
#include <unistd.h>

//./philo time time time (optional) returns 1 for error

void	eat(t_philo *philo)
{
	long long	dur;
	long long	curr;
	long long	start;//start of each cycle

	pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->main_struct->print);//
		printf("ID:%d taken left fork\n", philo->id);//
		pthread_mutex_unlock(&philo->main_struct->print);//
	pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->main_struct->print);//
		printf("ID:%d taken right fork\n", philo->id);//
		write(1,"0\n", 2);//
		pthread_mutex_unlock(&philo->main_struct->print);//
		write(1,"1\n", 2);//
	start = your_time();
	while (1)
	{
			write(1,"2\n", 2);//
	usleep(10);
	curr = your_time();
	dur = curr - start;
			pthread_mutex_lock(&philo->main_struct->print);//
			printf("ID:%d dur:%llu tabeteimashita\n", philo->id, dur);//
			pthread_mutex_unlock(&philo->main_struct->print);//
	if (dur == philo->main_struct->time_to_eat)
	{
								philo->full++;
			pthread_mutex_lock(&philo->main_struct->print);//
			printf("Gekkou desu\n");//
			pthread_mutex_unlock(&philo->main_struct->print);//
	pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_lock(&philo->main_struct->print);//
			printf("ID:%d dropped left fork\n", philo->id);//
			pthread_mutex_unlock(&philo->main_struct->print);//
	pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_lock(&philo->main_struct->print);
			printf("ID:%d dropped right fork\n", philo->id);
			pthread_mutex_unlock(&philo->main_struct->print);
	break ;
	}
	}
}

void	bed(t_philo *philo)
{
	long long	dur;
	long long	curr;
	long long	start;
	start = your_time();
	while(1)
	{
		usleep(10);
		curr = your_time();
		dur = curr - start;
		pthread_mutex_lock(&philo->main_struct->print);
		printf("ID:%d dur:%llu neteimashita\n", philo->id, dur);
		pthread_mutex_unlock(&philo->main_struct->print);
		if (dur == philo->main_struct->time_to_sleep)
		{
		pthread_mutex_lock(&philo->main_struct->print);
		printf("nemukunai desu\n");
		pthread_mutex_unlock(&philo->main_struct->print);
			break;
		}
	}
}

void	*routine(t_philo *philo)
{
	philo->lastmeal = your_time();
	pthread_mutex_lock(&philo->main_struct->print);
	printf("last meal:%llu\n", philo -> lastmeal);
	pthread_mutex_unlock(&philo->main_struct->print);
	int i = 0;
	if (philo->id % 2 == 0)
		usleep(42);
	if (philo->id % 2 == 1)
	{
		while(1)
		{
			eat(philo);
			if (philo->full == philo->main_struct->meal_amount)
				break;
			bed(philo);
			i++;
			if (i == 5)
				break ;
		}
	}
	// if (philo->id %2 == 0)
	// {
	// 	while(1)
	// 	{
	// 		bed(philo);
	// 		eat(philo);
	// 		if (philo->full == philo->main_struct->meal_amount)
	// 			break;
	// 		i++;
	// 		if (i == 5)
	// 			break ;
	// 	}
	// }
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
	ft_putendl("Malloc done");
	init_philo(info);
	return (0);
}

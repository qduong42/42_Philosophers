/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:37:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/06 16:53:07 by qduong           ###   ########.fr       */
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
		pthread_mutex_lock(&philo->main_struct->print);//
		printf("%05llu %d is sleeping\n", your_time() - philo->main_struct->p_start_time, philo->id);
		pthread_mutex_unlock(&philo->main_struct->print);//
	while(!philo->main_struct->dead)
	{
		usleep(100);
		curr = your_time();
		dur = curr - start;
		// pthread_mutex_lock(&philo->main_struct->print);
		// printf("ID:%d dur:%llu neteimashita\n", philo->id, dur);
		// pthread_mutex_unlock(&philo->main_struct->print);
		if (dur >= philo->main_struct->time_to_sleep)
		{
		// pthread_mutex_lock(&philo->main_struct->print);//
		// printf("nemukunai desu\n");//
		// pthread_mutex_unlock(&philo->main_struct->print);//
			break ;
		}
		else if (curr - philo->lastmeal >= philo->main_struct->time_to_eat)
		{
			pthread_mutex_lock(&(philo->main_struct->death));
			philo->main_struct->dead = 1;
			pthread_mutex_unlock(&(philo->main_struct->death));
			pthread_mutex_lock(&philo->main_struct->print);//
			printf("時間%llu二：ここに死んでいました\n", curr);
			pthread_mutex_unlock(&philo->main_struct->print);//
			pthread_detach(philo->thread);
			break ;
		}
	}
}

// idk what this function do pls help me
void	*routine(t_philo *philo)
{
	philo->lastmeal = your_time();
	pthread_mutex_lock(&(philo->main_struct->print));
	printf("last meal:%llu\n", philo->lastmeal);
	pthread_mutex_unlock(&(philo->main_struct->print));
	long long	c_time;
	if (philo->id % 2 == 0)
		usleep(42);
	if (philo->id % 2 == 1)
	{
		while(!philo->main_struct->dead)
		{
			c_time = your_time();
			int ima = c_time - philo->lastmeal;
			if (c_time - philo->lastmeal >= philo->main_struct->time_to_eat)
			{
				pthread_mutex_lock(&(philo->main_struct->death));
				philo->main_struct->dead = 1;
				pthread_mutex_unlock(&(philo->main_struct->death));
				pthread_mutex_lock(&philo->main_struct->print);//
				printf("%d三：ここに死んでいました\n",ima);
				pthread_mutex_unlock(&philo->main_struct->print);//
				pthread_detach(philo->thread);
				break ;
			}
			else
			{
			eat(philo);
			if (philo->full == philo->main_struct->meal_amount)
				break;
			bed(philo);
			pthread_mutex_lock(&philo->main_struct->print);//
			printf("%05llu %d is thinking\n", your_time() - philo->main_struct->p_start_time, philo->id);
			pthread_mutex_unlock(&philo->main_struct->print);//
			}
		}
	}
	if (philo->id %2 == 0)
	{
		while(!philo->main_struct->dead)
		{
			c_time = your_time();
			if (c_time - philo->lastmeal >= philo->main_struct->time_to_eat)
			{
				pthread_mutex_lock(&(philo->main_struct->death));
				philo->main_struct->dead = 1;
				pthread_mutex_unlock(&(philo->main_struct->death));
				pthread_mutex_lock(&philo->main_struct->print);//
				printf("四：ここに死んでいました\n");
				pthread_mutex_unlock(&philo->main_struct->print);//
				pthread_detach(philo->thread);
				break ;
			}
			else
			{
			bed(philo);
			eat(philo);
			pthread_mutex_lock(&philo->main_struct->print);//
			printf("%05llu %d is thinking\n", your_time() - philo->main_struct->p_start_time, philo->id);
			pthread_mutex_unlock(&philo->main_struct->print);//
			if (philo->full == philo->main_struct->meal_amount)
				break ;
			}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:32:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/23 15:45:26 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	death_print(t_struct *info, int i)
{
	pthread_mutex_unlock(&(info->last_meal));
	pthread_mutex_lock(&info->death);
	info->dead = 1;
	pthread_mutex_unlock(&info->death);
	pthread_mutex_lock(&info->print);
	printf("%05llu %d has died\n", ((your_time() - \
	info->p_start_time)), (i + 1));
	pthread_mutex_unlock(&info->print);
}

static int	full_check(t_struct *info)
{
	pthread_mutex_lock(&(info->last_meal));
	if (info->fullaf == info->philo_num)
	{
		pthread_mutex_unlock(&(info->last_meal));
		return (1);
	}
	pthread_mutex_unlock(&(info->last_meal));
	return (0);
}

static void	death_set(t_struct *info)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < info->philo_num)
		{
			pthread_mutex_lock(&(info->last_meal));
			if (info->philos[i].full == info->meal_amount)
			{
				pthread_mutex_unlock(&(info->last_meal));
				i++;
			}
			else if (your_time() - (info->philos[i].lastmeal) \
			>= info->time_to_die)
			{
				death_print(info, i);
				return ;
			}
			pthread_mutex_unlock(&(info->last_meal));
			usleep(69);
		}
		if (full_check(info))
			break ;
	}
}

static void	free_it(t_struct *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	free(info->fork);
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->death);
	pthread_mutex_destroy(&info->last_meal);
	free(info->philos);
}

int	main(int argc, char **argv)
{
	t_struct	info;

	if (argc > 6 || argc < 5)
	{
		write(STDERR_FILENO, HOW, sizeof(HOW));
		return (0);
	}
	if (initial_arg_check(argv, &info))
		return (write(STDERR_FILENO, HOW, sizeof(HOW)));
	if (parse_info(&info) == 1)
		ft_puterror("Failed to create mallocs or thread");
	if (threads_start(&info))
		ft_puterror("Failed to start thread");
	death_set(&info);
	if (threads_join(&info))
		ft_puterror("Failed to join");
	free_it(&info);
	return (0);
}

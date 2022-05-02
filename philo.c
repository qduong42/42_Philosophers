/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:37:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 02:56:32 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"
#include <unistd.h>

//./philo time time time (optional) returns 1 for error

void*	routine(t_philo *phil)
{
	int	i;
	i = 0;
	if (phil->id % 2 == 0)
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
}

int	parse_info(t_struct *info)
{
	int	i;

	i = 0;
	info->philos = malloc(info->philo_num * sizeof(t_philo));
	info->fork = malloc(info->philo_num * sizeof(pthread_mutex_t));
	if (!info->philos || !info->fork)
		return (1);
	while (i < info->philo_num) //ID will be 1, 2, 3 while i is 0, 1, 2
	{
		info->philos[i].id = i + 1;
		if (pthread_create(info->thread, NULL, &routine, &info->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	initial_arg_check(char **argv, t_struct *info)
{
	if (atoi_n_check(argv[1], &info->philo_num)||
	atoi_n_check(argv[2], &info->time_to_die)||
	atoi_n_check(argv[3], &info->time_to_eat)||
	atoi_n_check(argv[4], &info->time_to_sleep))
		return (1);
	if (argv[5])
		if(atoi_n_check(argv[5], &info->meal_amount))
			return (1);
	return (0);
}

int	atoi_n_check(char *argv, int *a)
{
	int	index;
	index = 0;
	long result;
	result = 0;
	if (argv[0] == '-')
		return (-1);
	if (argv[0] == '+')
		index++;
	while (argv[index])
	{
		if (argv[index] < '0' || argv[index] > '9')
			return (1);
		result = result * 10 + (argv[index] - '0');
		index ++;
		if (result > INT_MAX)
			return (1);
	}
	*a = (int)result;
	return (0);
}

long long	your_time(void)
{
	_STRUCT_TIMEVAL time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

init_philo(t_struct *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		info->philos[i].lastmeal = your_time();
		i++;
	}
}

int	main (int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		write(STDERR_FILENO, HOW, sizeof(HOW));
		return (0);
	}
	t_struct info;
	if (initial_arg_check(argv, &info))
		write(STDERR_FILENO, HOW, sizeof(HOW));
	if (parse_info(&info))
		write(1, "Failed to create mallocs or thread", 35);
	if (create_mutex(&info))
		write(1, "Failed to create mutexes", 25);
	init_philo(&info);
	return (0);
}

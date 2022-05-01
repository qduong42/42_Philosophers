/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:37:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/01 18:32:27 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"
#include <unistd.h>

//./philo time time time (optional)

int	main (int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		write(STDERR_FILENO, how, sizeof(how));
		return (0);
	}
	t_struct info;
	if (initial_arg_check(argv, &info))
		write(STDERR_FILENO, how, sizeof(how));
	parse_info(&info);
	create_mutex(&info);
}

void*	routine(t_struct *info)
{
	
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
	}
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
		info->philos->id = i + 1;
		if (pthread_create(info->thread, NULL, &routine, &info) != 0)
			return (1);
		i++;
		if (info->philos->id % 2 == 0)
			usleep(42);
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

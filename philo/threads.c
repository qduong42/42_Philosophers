/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:34:12 by qduong            #+#    #+#             */
/*   Updated: 2022/05/23 16:58:44 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_join(t_struct *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_join(info->philos[i].thread, NULL) == 1)
			return (1);
		i++;
	}
	return (0);
}
	//printf("P_Start Time:%llu\n", info->p_start_time);
	//ID will be 1, 2, 3 while i is 0, 1, 2
	// pthread_mutex_lock(&info->print);//
	// ft_putendl("Thread created");//
	// pthread_mutex_unlock(&info->print);//

int	threads_start(t_struct *info)
{
	int	i;

	i = 0;
	info->p_start_time = your_time();
	while (i < info->philo_num)
	{
		if (pthread_create(&info->philos[i].thread, NULL, \
		(void *(*)(void *)) routine, &(info->philos[i])) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	create_mutex(t_struct *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&info->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->death, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info->last_meal, NULL) != 0)
		return (1);
	return (0);
}

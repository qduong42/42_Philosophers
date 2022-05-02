/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:34:12 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 16:37:59 by qduong           ###   ########.fr       */
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
		ft_putendl("Thread joined");
		i++;
	}
	return (0);
}

int	threads_start(t_struct *info)
{
	int	i;

	i = 0;
	info->p_start_time = your_time();
	printf("P_Start Time:%llu\n", info->p_start_time);
	while (i < info->philo_num) //ID will be 1, 2, 3 while i is 0, 1, 2
	{
		if (pthread_create(&info->philos[i].thread, NULL, \
		(void *(*)(void *)) routine, &info->philos[i]) != 0)
			return (1);
		pthread_mutex_lock(&info->print);
		ft_putendl("Thread created");
		pthread_mutex_unlock(&info->print);
		i++;
	}
	return (0);
}

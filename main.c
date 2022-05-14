/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:32:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/14 21:01:36 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_set(t_struct *info)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < info->philo_num)
		{
			if (your_time() - info->philos[i].lastmeal >= info->time_to_die)
			{
				pthread_mutex_lock(&info->death);
				info->dead = 1;
				pthread_mutex_unlock(&info->death);
				return ;
			}
			pthread_mutex_unlock(&info->death);
			i++;
		usleep(29);
		}
	}
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
		write(STDERR_FILENO, HOW, sizeof(HOW));
	if (parse_info(&info) == 1)
		ft_puterror("Failed to create mallocs or thread");
	if (threads_start(&info))
		ft_puterror("Failed to start thread");
	death_set(&info);	
	//if (threads_join(&info))
	// 	ft_puterror("Failed to join");
	//destroy_stuff(&info);
	return (0);
}

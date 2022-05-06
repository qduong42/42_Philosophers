/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:32:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/06 16:51:57 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_struct *info)
{
	while(1)
	{
		pthread_mutex_lock(&(info->death));
		if (info->dead == 1)
		{
			pthread_mutex_lock(&info->print);//
			printf("お前はもう死んでいる\n");
			pthread_mutex_unlock(&info->print);//
			pthread_mutex_unlock(&(info->death));
			break ;
		}
		pthread_mutex_unlock(&info->death);
		usleep(10);
	}
	return (1);
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
	if (death_check(&info))
		return (write(1, "Died\n", 5));
	if (threads_join(&info))
		ft_puterror("Failed to join");
	//destroy_stuff(&info);
	return (0);
}

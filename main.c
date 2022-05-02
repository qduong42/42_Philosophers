/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:32:30 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 16:32:36 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (create_mutex(&info))
		ft_puterror("Failed to create mutexes");
	if (threads_start(&info))
		ft_puterror("Failed to start thread");
	if (threads_join(&info))
		ft_puterror("Failed to join");
	return (0);
}

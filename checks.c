/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:30:34 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 21:33:12 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initial_arg_check(char **argv, t_struct *info)
{
	info->meal_amount = -1;
	if (atoi_n_check(argv[1], &info->philo_num) || \
	atoi_n_check(argv[2], &info -> time_to_die) || \
	atoi_n_check(argv[3], &info -> time_to_eat) || \
	atoi_n_check(argv[4], &info -> time_to_sleep))
		return (1);
	if (argv[5] && (atoi_n_check(argv[5], &info->meal_amount) || \
	info->meal_amount <= 0))
		return (1);
	ft_putendl("arg check done");
	return (0);
}

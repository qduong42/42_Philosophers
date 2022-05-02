/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:30:34 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 16:33:44 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initial_arg_check(char **argv, t_struct *info)
{
	if (atoi_n_check(argv[1], &info->philo_num) || \
	atoi_n_check(argv[2], &info -> time_to_die) || \
	atoi_n_check(argv[3], &info -> time_to_eat) || \
	atoi_n_check(argv[4], &info -> time_to_sleep))
		return (1);
	if (argv[5] && atoi_n_check(argv[5], &info->meal_amount))
		return (1);
	ft_putendl("arg check done");
	return (0);
}

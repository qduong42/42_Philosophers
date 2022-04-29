/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:37:30 by qduong            #+#    #+#             */
/*   Updated: 2022/04/30 00:26:13 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"
#include <unistd.h>

typedef struct s_struct 
{
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meal_amount;
}				t_struct;

//./philo time time time (optional)

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

int initial_arg_check(char **argv, t_struct *info)
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

int main (int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		write(STDERR_FILENO, how, sizeof(how));
		return (0);
	}
	t_struct info;
	if (initial_arg_check(argv, &info))
		write(STDERR_FILENO, how, sizeof(how));
}

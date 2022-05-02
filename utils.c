/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:05:50 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 16:32:59 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_puterror(char *s)
{
	write (STDERR_FILENO, "Error\n", 6);
	while (*s)
	{
		(write (STDERR_FILENO, &s, 1));
		s++;
	}
	write (STDERR_FILENO, "\n", 1);
}

void	ft_putendl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int	atoi_n_check(char *argv, int *a)
{
	int		index;
	long	result;

	index = 0;
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
		if (result > INT_MAX || result == 0)
			return (1);
	}
	*a = (int)result;
	return (0);
}

long long	your_time(void)
{
	_STRUCT_TIMEVAL	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

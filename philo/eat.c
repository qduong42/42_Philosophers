/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:58:58 by qduong            #+#    #+#             */
/*   Updated: 2022/05/24 00:05:12 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_check(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->main_struct->print);
	pthread_mutex_lock(&philo->main_struct->death);
	if (!philo->main_struct->dead)
	{
		printf("%05llu %d %s\n", ((your_time() - \
		philo->main_struct->p_start_time)), philo->id, s);
	}
	pthread_mutex_unlock(&philo->main_struct->death);
	pthread_mutex_unlock(&philo->main_struct->print);
}

	// 	death_check(philo, "has dropped a left fork");
	// 	death_check(philo, "has dropped a right fork");

static void	set_full(t_philo *philo)
{
	pthread_mutex_lock(&(philo->main_struct->last_meal));
	philo->full++;
	//philo->lastmeal = your_time();
	if (philo->full == philo->main_struct->meal_amount)
		philo->main_struct->fullaf++;
	pthread_mutex_unlock(&(philo->main_struct->last_meal));
}

void	eat(t_philo *philo)
{
	long long	dur;
	long long	curr;
	long long	start;

	pthread_mutex_lock(&(philo->main_struct->last_meal));
	philo->lastmeal = your_time();
	pthread_mutex_unlock(&(philo->main_struct->last_meal));
	pthread_mutex_lock(philo->left_fork);
	death_check(philo, "has taken a left fork");
	pthread_mutex_lock(philo->right_fork);
	death_check(philo, "has taken a right fork");
	start = your_time();
	death_check(philo, "is eating");
	while (1)
	{
		usleep(100);
		curr = your_time();
		dur = curr - start;
		if (dur >= philo->main_struct->time_to_eat)
		{
			set_full(philo);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
	}
}

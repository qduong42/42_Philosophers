/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 10:58:53 by qduong            #+#    #+#             */
/*   Updated: 2022/05/01 19:22:59 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define how "Use by ./philo philo_num time_to_die time_to_eat time_to_sleep\n"

/*
**Checks
*/

int	atoi_n_check(char *argv, int *a);

typedef struct s_struct 
{
	int			philo_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meal_amount;
	t_philo		*philos;
	pthread_mutex_t		*fork;
	pthread_t	thread;
}				t_struct;

typedef struct s_philo
{
	int				id;
	int				lastmeal;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}				t_philo;

# endif
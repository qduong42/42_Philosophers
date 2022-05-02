/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 10:58:53 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 02:41:34 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define HOW "Use by ./philo philo_num time_to_die time_to_eat time_to_sleep\n"

/*
**Checks
*/

int	atoi_n_check(char *argv, int *a);

typedef struct s_struct 
{
	int					philo_num; //set in initial_arg_Check
	int					time_to_die; //set in initial_arg_Check
	int					time_to_eat; //set in initial_arg_Check
	int					time_to_sleep; //set in initial_arg_Check
	int					meal_amount;  //set in initial_arg_Check
	t_philo				*philos;
	pthread_mutex_t		*fork; //malloced in parse info
	pthread_mutex_t		print; //init in create_mutex
	pthread_mutex_t		death; //init in create_mutex
	pthread_t			thread; //stores info from pthread create
}				t_struct;

typedef struct s_philo
{
	int				id; //inited
	int				lastmeal; //init_philo
	pthread_mutex_t	*left_fork; //init philo
	pthread_mutex_t	*right_fork; //init philo
}				t_philo;

# endif
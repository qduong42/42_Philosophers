/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 10:58:53 by qduong            #+#    #+#             */
/*   Updated: 2022/05/02 20:56:46 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

# define HOW "Use by ./philo philo_num time_to_die time_to_eat time_to_sleep\n"

typedef struct s_struct	t_struct;

typedef struct s_philo
{
	t_struct			*main_struct;
	int					id; //init_philo
	pthread_mutex_t		*left_fork; //init philo
	pthread_mutex_t		*right_fork; //init philo
	long long			lastmeal; //threads start & last meal time to calc death
	int					full;// number of people full
	pthread_t			thread; //stores info from pthread create
}				t_philo;

typedef struct s_struct
{
	int					philo_num; //set in initial_arg_Check
	int					time_to_die; //set in initial_arg_Check
	int					time_to_eat; //set in initial_arg_Check
	int					time_to_sleep; //set in initial_arg_Check
	int					meal_amount; //set in initial_arg_Check
	long long			p_start_time; //start time of program -> threads start
	long long			lag;
	int					dead;//dead or not
	t_philo				*philos;
	pthread_mutex_t		*fork; //malloced in parse info
	pthread_mutex_t		print; //init in create_mutex
	pthread_mutex_t		death; //init in create_mutex
}				t_struct;

/*
**Checks
*/

int			atoi_n_check(char *argv, int *a);
int			initial_arg_check(char **argv, t_struct *info);

/*
**Utils
*/

void		ft_puterror(char *s);
void		ft_putendl(char *s);
long long	your_time(void);

/*
** Threads & mutexes
*/

int			threads_join(t_struct *info);
int			threads_start(t_struct *info);
void		*routine(t_philo *philo);
int			create_mutex(t_struct *info);

/*
** initials
*/

int			init_philo(t_struct *info);
int			parse_info(t_struct *info);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 10:58:53 by qduong            #+#    #+#             */
/*   Updated: 2022/05/18 12:06:51 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long long			lastmeal;
	int					full;
	pthread_t			thread;
}				t_philo;

typedef struct s_struct
{
	int					philo_num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_amount;
	long long			p_start_time;
	pthread_mutex_t		last_meal;
	int					dead;
	t_philo				*philos;
	int					fullaf;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	pthread_mutex_t		death;
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
void		death_check(t_philo *philo, char *s);

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

int			parse_info(t_struct *info);

/*
**sub-routines
*/

void		eat(t_philo *philo);

#endif
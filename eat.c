#include "philo.h"

void	death_check(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->main_struct->print);//
	pthread_mutex_lock(&philo->main_struct->death);
	if (!philo->main_struct->dead)
	{
		printf("%05llu %d %s\n", ((your_time() - philo->main_struct->p_start_time)), philo->id, s);//
	}
	pthread_mutex_unlock(&philo->main_struct->death);
	pthread_mutex_unlock(&philo->main_struct->print);
}

void	eat(t_philo *philo)
{
	long long	dur;
	long long	curr;
	long long	start;//start of each cycle
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
			pthread_mutex_lock(&(philo->main_struct->last_meal));
			philo->full++;
			philo->lastmeal = your_time();
			if (philo->full == philo->main_struct->meal_amount)
			{
				philo->main_struct->fullaf++;
			}
			pthread_mutex_unlock(&(philo->main_struct->last_meal));
			pthread_mutex_unlock(philo->left_fork);
			// 	death_check(philo, "has dropped a left fork");
			pthread_mutex_unlock(philo->right_fork);
			// 	death_check(philo, "has dropped a right fork");
			break ;
		}
	}
}

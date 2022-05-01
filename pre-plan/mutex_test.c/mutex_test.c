/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:10:17 by qduong            #+#    #+#             */
/*   Updated: 2022/05/01 19:45:52 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int b = 0;

void*	routine(pthread_mutex_t *a)
{
	//pthread_mutex_lock(a);
	pthread_mutex_lock(a);
	b = 5;
	sleep(3);
	pthread_mutex_unlock(a);
	return (NULL);
}
void*	routine_2(/* pthread_mutex_t *a */)
{
	//pthread_mutex_lock(a);
	printf("%d\n", b);
	//pthread_mutex_unlock(a);
	return (NULL);
}
int main()
{
	pthread_t thread1;
	pthread_t thread2;
	// pthread_t thread3;
	pthread_mutex_t a;
	printf("%d\n", b);
	pthread_mutex_init(&a, NULL);
	if (pthread_create(&thread1, NULL, (void *(*)(void *))&routine, &a) != 0)
		write (2, "No", 2);
	if (pthread_create(&thread2, NULL, (void *(*)(void *))&routine_2, &a) != 0)
		write (2, "No", 2);
	// if (pthread_create(&thread3, NULL, (void *(*)(void *))&routine, &a) != 0)
	// 	write (2, "No", 2);
	if (pthread_join(thread1, NULL) != 0)
		write (2, "Go", 2);
	if (pthread_join(thread2, NULL) != 0)
		write (2, "Go", 2);
	// if (pthread_join(thread3, NULL) != 0)
	// 	write (2, "Go", 2);
	return (0);
}
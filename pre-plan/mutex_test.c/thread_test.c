/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 18:34:00 by qduong            #+#    #+#             */
/*   Updated: 2022/05/01 19:04:46 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# include <pthread.h>
#include <unistd.h>

void*	routine()
{
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	write(1, "HADFAWFADWDWADDAADW\n", 20);
	return (NULL);
}

int main(/* int argc, char** argv */)
{
	/* if (argc == 10 || argv[0][0] == 'H')
		return 0; */
	pthread_t thread1;
	//pthread_t thread2;
	if (pthread_create(&thread1, NULL, &routine, NULL) != 0)
		write (2, "No", 2);
	if (pthread_join(thread1, NULL) != 0)
		write (2, "Go", 2);
		usleep(1);
		return 0;
}
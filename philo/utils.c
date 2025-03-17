/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:29:46 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/17 05:01:30 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_forks(pthread_mutex_t *lock, t_philo *philo, int forks_index[2])
{
	pthread_mutex_lock(lock);
	if (philo->forks[forks_index[0]] == 'a'
		&& philo->forks[forks_index[1]] == 'a')
		return (pthread_mutex_unlock(lock), 1);
	pthread_mutex_unlock(lock);
	return (0);
}

void	dying_alone(pthread_t *threads, int *args, char *forks)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	usleep(args[1] * 1000);
	printf("%li %i died\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000), 1);
	free(threads);
	free(args);
	free(forks);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:14:39 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/09 17:11:37 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	die(t_philo	*philo, int forks_index[2], pthread_mutex_t *lock)
{
	struct timeval		tv;
	int					tmp;

	pthread_mutex_lock(lock);
	tmp = philo->args[1];
	pthread_mutex_unlock(lock);
	gettimeofday(&tv, NULL);
	printf("%lli %i is thinking\n", timestamp(&tv, lock + 2), philo->number + 1);
	while (!check_forks(lock, philo, forks_index))
	{
		gettimeofday(&tv, NULL);
		if (((tv.tv_sec * 1000) + tv.tv_usec / 1000) - philo->age
			> tmp)
		{
			pthread_mutex_lock(lock);
			gettimeofday((struct timeval *)philo->args[7], NULL);
			philo->args[5] = philo->number + 1;
			pthread_mutex_unlock(lock);
			return (1);
		}
	}
	return (0);
}

void	eat_then_sleep(t_philo	*philo, int forks_index[2],
		pthread_mutex_t *lock)
{
	struct timeval		tv;
	int					arg;

	gettimeofday(&tv, NULL);
	printf("%lli %i has taken a fork\n",
		timestamp(&tv, lock + 2), philo->number + 1);
	printf("%lli %i has taken a fork\n",
		timestamp(&tv, lock + 2), philo->number + 1);
	philo->forks[forks_index[1]] = 'u';
	philo->forks[forks_index[0]] = 'u';
	printf("%lli %i is eating\n", timestamp(&tv, lock + 2), philo->number + 1);
	arg = philo->args[2];
	pthread_mutex_unlock(lock + 1);
	philo->age = timenow();
	usleep(arg * 1000);
	pthread_mutex_lock(lock + 1);
	philo->forks[forks_index[1]] = 'a';
	philo->forks[forks_index[0]] = 'a';
	pthread_mutex_unlock(lock + 1);
	pthread_mutex_lock(lock);
	arg = philo->args[3];
	(pthread_mutex_unlock(lock), gettimeofday(&tv, NULL));
	printf("%lli %i is sleeping\n", timestamp(&tv, lock + 2), philo->number + 1);
	usleep(arg * 1000);
}

void	starving(pthread_t *threads, long long *args, char *forks)
{
	usleep(args[1] * 1000);
	printf("%lli %i died\n", args[1], 1);
	free(threads);
	free(args);
	free(forks);
}

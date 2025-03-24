/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:29:46 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/22 21:42:20 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_forks(pthread_mutex_t *lock, t_philo *philo, int forks_index[2])
{
	pthread_mutex_lock(lock + 1);
	if (philo->forks[forks_index[0]] == 'a'
		&& philo->forks[forks_index[1]] == 'a')
		return (pthread_mutex_unlock(lock + 1), 1);
	pthread_mutex_unlock(lock + 1);
	return (0);
}

void	dying_alone(pthread_t *threads, long long *args, char *forks)
{
	usleep(args[1] * 1000);
	printf("%lli %i died\n", args[1], 1);
	free(threads);
	free(args);
	free(forks);
}

int	finish(pthread_mutex_t *lock, long long *args, char *forks, pthread_t *threads)
{
	pthread_mutex_lock(lock);
	free(args);
	pthread_mutex_lock(lock + 1);
	free(forks);
	free(threads);
	return (0);
}

long	timestamp(struct timeval *arg_tv, pthread_mutex_t *lock)
{
	static struct timeval		tv;
	static int					i;
	long						time;
	long						time2;

	pthread_mutex_lock(lock);
	if (i == 0)
		gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (arg_tv == NULL)
		return (pthread_mutex_unlock(lock), time);
	time2 = (arg_tv->tv_sec * 1000) + (arg_tv->tv_usec / 1000);
	i = 1;
	pthread_mutex_unlock(lock);
	return (time2 - time);
}

void	increment(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->lock);
	if (i == philo->args[4])
		philo->args[6]++;
	pthread_mutex_unlock(philo->lock);
}

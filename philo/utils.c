/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:29:46 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/10 13:44:38 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_forks(pthread_mutex_t *lock, t_philo *philo, int forks_index[2])
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(lock + 1);
	if (philo->forks[forks_index[0]] == 'a'
		&& philo->forks[forks_index[1]] != 'a')
	{
		philo->forks[forks_index[0]] = philo->number;
		printf("%lli %i has taken a fork\n",
			timestamp(&tv, lock + 2), philo->number + 1);
	}
	if (philo->forks[forks_index[0]] != 'a'
		&& philo->forks[forks_index[1]] == 'a')
	{
		philo->forks[forks_index[1]] = philo->number;
		printf("%lli %i has taken a fork\n",
			timestamp(&tv, lock + 2), philo->number + 1);
	}
	if ((philo->forks[forks_index[0]] == 'a' || philo->forks[forks_index[0]] == philo->number)
		&& (philo->forks[forks_index[1]] == 'a' || philo->forks[forks_index[1]] == philo->number))
		return (pthread_mutex_unlock(lock + 1), 1);
	pthread_mutex_unlock(lock + 1);
	return (0);
}

int	check_forks2(t_philo *philo, int forks_index[2])
{
	if ((philo->forks[forks_index[0]] == 'a' || philo->forks[forks_index[0]] == philo->number)
		&& (philo->forks[forks_index[1]] == 'a' || philo->forks[forks_index[1]] == philo->number))
		return (1);
	return (0);
}

int	finish(pthread_mutex_t *lock, long long *args,
		char *forks, pthread_t *threads)
{
	pthread_mutex_lock(lock);
	pthread_mutex_lock(lock + 1);
	free(args);
	free(forks);
	free(threads);
	return (0);
}

long long	timestamp(struct timeval *arg_tv, pthread_mutex_t *lock)
{
	struct timeval		tv;
	static int			i;
	static long long	time;
	long long			time2;

	if (arg_tv == NULL || lock == NULL)
		return (-1);
	pthread_mutex_lock(lock);
	if (i == 0)
	{
		gettimeofday(&tv, NULL);
		time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
	i = 1;
	time2 = (arg_tv->tv_sec * 1000) + (arg_tv->tv_usec / 1000);
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

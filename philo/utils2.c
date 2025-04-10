/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:14:39 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/10 14:00:18 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	think(t_philo	*philo, int forks_index[2], pthread_mutex_t *lock)
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
		if (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - philo->age
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

int	eat_then_sleep(t_philo	*philo, int forks_index[2],
	pthread_mutex_t *lock)
{
	struct timeval		tv;
	int					arg;
	int					arg2;

	gettimeofday(&tv, NULL);
	picking_forks(&tv, philo, forks_index);
	printf("%lli %i is eating\n", timestamp(&tv, lock + 2), philo->number + 1);
	arg = philo->args[2];
	arg2 = philo->args[1];
	pthread_mutex_unlock(lock + 1);
	philo->age = timenow();
	if (!ft_usleep(arg, arg2))
		return (0);
	pthread_mutex_lock(lock + 1);
	philo->forks[forks_index[1]] = 'a';
	philo->forks[forks_index[0]] = 'a';
	pthread_mutex_unlock(lock + 1);
	pthread_mutex_lock(lock);
	arg = philo->args[3];
	arg2 = philo->args[1];
	(pthread_mutex_unlock(lock), gettimeofday(&tv, NULL));
	printf("%lli %i is sleeping\n", timestamp(&tv, lock + 2), philo->number + 1);
	if (!ft_usleep(arg, arg2))
		return (0);
	return (1);
}

void	starving(pthread_t *threads, long long *args, char *forks)
{
	usleep(args[1] * 1000);
	printf("%lli %i died\n", args[1], 1);
	free(threads);
	free(args);
	free(forks);
}

int	ft_usleep(int ms, int time2die)
{
	struct timeval	tv;
	long long		start;
	long long		now;

	gettimeofday(&tv, NULL);
	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	now = start;
	while (now - start < ms)
	{
		if (now - start >= time2die)
			return (0);
		usleep(100);
		gettimeofday(&tv, NULL);
		now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
	return (1);
}

void	exit_thread(t_philo *philo)
{
	pthread_mutex_t		*lock;

	lock = philo->lock;
	pthread_mutex_lock(lock);
	free(philo);
	pthread_mutex_unlock(lock);
}

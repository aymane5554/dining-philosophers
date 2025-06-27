/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:29:46 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/27 13:20:47 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	starving(pthread_t *threads, const long long *args, char *forks)
{
	usleep(args[1] * 1000);
	printf("%lli %i died\n", args[1], 1);
	free(threads);
	free((long long *)args);
	free(forks);
}

int	ft_usleep(int ms, int time2die, long long last_meal)
{
	struct timeval	tv;
	long long		start;
	long long		now;
	long long		age;

	gettimeofday(&tv, NULL);
	age = last_meal;
	now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	start = now;
	while (now - start < ms)
	{
		if (now - age >= time2die)
			return (1);
		usleep(100);
		gettimeofday(&tv, NULL);
		now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
	if (now - age >= time2die)
		return (1);
	return (0);
}

int	start_eating(t_philo *philo, int *meals,
		char *picked_forks, int coordinates[2])
{
	if (eating(philo, coordinates))
		return (death(philo), 1);
	if (philo->args[4] != -1)
		(*meals)++;
	*picked_forks = 0;
	return (0);
}

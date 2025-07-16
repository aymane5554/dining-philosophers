/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:29:46 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/16 15:59:13 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	starving(const long long *args)
{
	printf("0 1 has taken a fork\n");
	usleep(args[1] * 1000);
	printf("%lli %i died\n", args[1], 1);
	free((long long *)args);
}

int	ft_usleep(int ms, t_philo *philo)
{
	struct timeval	tv;
	long long		start;
	long long		now;
	long long		age;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(philo->lock);
	age = *(philo->age);
	pthread_mutex_unlock(philo->lock);
	now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	start = now;
	while (now - start < ms)
	{
		if (now - age > philo->args[1])
			return (1);
		if (end(0, philo->lock + 1))
			return (2);
		usleep(100);
		gettimeofday(&tv, NULL);
		now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
	if (now - age > philo->args[1])
		return (1);
	return (0);
}

t_philo	**create_philo_struct(const long long *args,
		pthread_mutex_t *locks, long long *info, long long *philo_age)
{
	t_philo		**tmp;
	int			j;

	j = 0;
	tmp = malloc(sizeof(t_philo *) * args[0]);
	if (!tmp)
		return (NULL);
	while (j < args[0])
	{
		tmp[j] = malloc(sizeof(t_philo));
		if (!tmp[j])
		{
			while (j >= 0)
				(free(tmp[j]), j--);
			return (free(tmp), NULL);
		}
		tmp[j]->args = args;
		tmp[j]->lock = locks;
		tmp[j]->info = info;
		tmp[j]->number = j;
		tmp[j]->age = philo_age + j;
		j++;
	}
	return (tmp);
}

void	multiple_free(void *first, void *second, void *third, void *forth)
{
	free(first);
	free(second);
	free(third);
	free(forth);
}

void	put_forks_(t_philo *philo, int coordinates[2])
{
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
}

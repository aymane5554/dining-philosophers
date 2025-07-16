/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:20:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/16 16:38:58 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_all(pthread_mutex_t *locks, int n)
{
	int	i;

	pthread_mutex_unlock(locks + 0);
	pthread_mutex_unlock(locks + 1);
	i = 0;
	while (i < n)
	{
		pthread_mutex_unlock(locks + 2 + i);
		i++;
	}
}

int	eating(t_philo *philo, int coordinates[2], int *meals)
{
	int	ret;

	if (!end(0, philo->lock + 1))
		printf("%lld %d is eating\n",
			timenow() - philo->args[5], philo->number + 1);
	pthread_mutex_lock(philo->lock);
	*(philo->age) = timenow();
	pthread_mutex_unlock(philo->lock);
	if (check(philo->args[2], philo, &ret))
		return (ret);
	put_forks(philo, coordinates);
	if (philo->args[4] != -1)
		(*meals)++;
	if (*meals == philo->args[4])
		return (pthread_mutex_lock(philo->lock), philo->info[1]++,
			*(philo->age) = 0, pthread_mutex_unlock(philo->lock), 2);
	if (!end(0, philo->lock + 1))
		printf("%lld %d is sleeping\n",
			timenow() - philo->args[5], philo->number + 1);
	if (check(philo->args[3], philo, &ret))
		return (ret);
	return (0);
}

char	pick_forks(t_philo *philo, int coordinates[2])
{
	if (!end(0, philo->lock + 1))
		printf("%lld %d is thinking\n",
			timenow() - philo->args[5], philo->number + 1);
	if (end(0, philo->lock + 1))
		return (1);
	pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
	if (!end(0, philo->lock + 1))
		printf("%lld %d has taken a fork\n",
			timenow() - philo->args[5], philo->number + 1);
	if (end(0, philo->lock + 1))
		return (1);
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	if (!end(0, philo->lock + 1))
		printf("%lld %d has taken a fork\n",
			timenow() - philo->args[5], philo->number + 1);
	return (0);
}

char	pick_forks_(t_philo *philo, int coordinates[2])
{
	if (!end(0, philo->lock + 1))
		printf("%lld %d is thinking\n",
			timenow() - philo->args[5], philo->number + 1);
	if (end(0, philo->lock + 1))
		return (1);
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	if (!end(0, philo->lock + 1))
		printf("%lld %d has taken a fork\n",
			timenow() - philo->args[5], philo->number + 1);
	if (end(0, philo->lock + 1))
		return (1);
	pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
	if (!end(0, philo->lock + 1))
		printf("%lld %d has taken a fork\n",
			timenow() - philo->args[5], philo->number + 1);
	return (0);
}

void	*death(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	philo->info[0] = philo->number + 1;
	philo->info[2] = timenow() - philo->args[5];
	pthread_mutex_unlock(philo->lock);
	free(philo);
	return (NULL);
}

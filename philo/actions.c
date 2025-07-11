/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:20:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/11 12:02:58 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo, int coordinates[2], int *meals)
{
	int	ret;

	pthread_mutex_lock(philo->lock);
	if (!end(0, philo->lock + 1))
		printf("%lld %d is eating\n",
			timenow() - philo->info[3], philo->number + 1);
	(pthread_mutex_unlock(philo->lock), philo->age = timenow());
	if (check(philo->args[2], philo, &ret))
		return (ret);
	pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
	philo->forks[coordinates[0]] = 'a';
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	philo->forks[coordinates[1]] = 'a';
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
	if (philo->args[4] != -1)
		(*meals)++;
	if (*meals == philo->args[4])
		(pthread_mutex_lock(philo->lock), philo->info[1]++,
			pthread_mutex_unlock(philo->lock));
	pthread_mutex_lock(philo->lock);
	if (!end(0, philo->lock + 1))
		printf("%lld %d is sleeping\n",
			timenow() - philo->info[3], philo->number + 1);
	pthread_mutex_unlock(philo->lock);
	if (check(philo->args[3], philo, &ret))
		return (ret);
	return (0);
}

static int	pick_forks_1(t_philo *philo, int coordinates[2],
			char *picked_forks)
{
	int	tmp;

	tmp = -1;
	pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
	if (philo->forks[coordinates[0]] == 'a')
	{
		philo->forks[coordinates[0]] = 'u';
		tmp = coordinates[0];
		(*picked_forks)++;
	}
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
	if (tmp == coordinates[0])
	{
		pthread_mutex_lock(philo->lock);
		if (!end(0, philo->lock + 1))
			printf("%lld %d has taken a fork\n",
				timenow() - philo->info[3], philo->number + 1);
		pthread_mutex_unlock(philo->lock);
	}
	return (tmp);
}

static int	pick_forks_2(t_philo *philo, int coordinates[2],
			char *picked_forks)
{
	int	tmp;

	tmp = -1;
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	if (philo->forks[coordinates[1]] == 'a')
	{
		philo->forks[coordinates[1]] = 'u';
		tmp = coordinates[1];
		(*picked_forks)++;
	}
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
	if (tmp == coordinates[1])
	{
		pthread_mutex_lock(philo->lock);
		if (!end(0, philo->lock + 1))
			printf("%lld %d has taken a fork\n",
				timenow() - philo->info[3], philo->number + 1);
		pthread_mutex_unlock(philo->lock);
	}
	return (tmp);
}

char	pick_forks(t_philo *philo, int coordinates[2], int *picked)
{
	char	picked_forks;
	int		tmp;
	int		tmp2;

	picked_forks = 0;
	*picked = -1;
	tmp = pick_forks_1(philo, coordinates, &picked_forks);
	tmp2 = pick_forks_2(philo, coordinates, &picked_forks);
	if (picked_forks == 1)
	{
		if (tmp != -1)
			*picked = tmp;
		else
			*picked = tmp2;
	}
	return (picked_forks);
}

void	*death(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	philo->info[0] = philo->number + 1;
	philo->info[2] = timenow() - philo->info[3];
	pthread_mutex_unlock(philo->lock);
	free(philo);
	return (NULL);
}

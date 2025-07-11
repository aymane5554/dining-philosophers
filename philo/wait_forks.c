/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:06:59 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/11 12:02:22 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pick_first_fork(t_philo *philo, int coordinates[2], int *count)
{
	int	p;

	p = 0;
	pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
	if (philo->forks[coordinates[0]] == 'a')
	{
		philo->forks[coordinates[0]] = 'u';
		(*count)++;
		p = 1;
	}
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
	if (p)
	{
		pthread_mutex_lock(philo->lock);
		if (!end(0, philo->lock + 1))
			printf("%lld %d has taken a fork\n",
				timenow() - philo->info[3], philo->number + 1);
		pthread_mutex_unlock(philo->lock);
		p = 0;
	}
}

static void	pick_second_fork(t_philo *philo, int coordinates[2], int *count)
{
	int	p;

	p = 0;
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	if (philo->forks[coordinates[1]] == 'a')
	{
		philo->forks[coordinates[1]] = 'u';
		(*count)++;
		p = 1;
	}
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
	if (p)
	{
		pthread_mutex_lock(philo->lock);
		if (!end(0, philo->lock + 1))
			printf("%lld %d has taken a fork\n",
				timenow() - philo->info[3], philo->number + 1);
		pthread_mutex_unlock(philo->lock);
		p = 0;
	}
}

static int	wait_forks(t_philo *philo, int coordinates[2])
{
	int		count;

	count = 0;
	while (timenow() - philo->age < philo->args[1] && !end(0, philo->lock + 1))
	{
		pick_first_fork(philo, coordinates, &count);
		pick_second_fork(philo, coordinates, &count);
		if (count == 2)
			return (0);
		usleep(100);
	}
	if (end(0, philo->lock + 1))
		return (2);
	return (1);
}

static int	wait_fork_(t_philo *philo,
				int fork_needed)
{
	pthread_mutex_lock(philo->lock + 2 + fork_needed);
	if (philo->forks[fork_needed] == 'a')
	{
		philo->forks[fork_needed] = 'u';
		pthread_mutex_unlock(philo->lock + 2 + fork_needed);
		pthread_mutex_lock(philo->lock);
		if (!end(0, philo->lock + 1))
			printf("%lld %d has taken a fork\n",
				timenow() - philo->info[3], philo->number + 1);
		pthread_mutex_unlock(philo->lock);
		return (1);
	}
	pthread_mutex_unlock(philo->lock + 2 + fork_needed);
	return (0);
}

int	wait_fork(t_philo *philo, int coordinates[2], int picked)
{
	int	fork_needed;

	pthread_mutex_lock(philo->lock);
	if (!end(0, philo->lock + 1))
		printf("%lld %d is thinking\n",
			timenow() - philo->info[3], philo->number + 1);
	pthread_mutex_unlock(philo->lock);
	if (picked == -1)
		return (wait_forks(philo, coordinates));
	if (picked == coordinates[0])
		fork_needed = coordinates[1];
	if (picked == coordinates[1])
		fork_needed = coordinates[0];
	while (timenow() - philo->age < philo->args[1] && !end(0, philo->lock + 1))
	{
		if (wait_fork_(philo, fork_needed))
			return (0);
		usleep(100);
	}
	if (end(0, philo->lock + 1))
		return (2);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:12:13 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/11 15:00:27 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	end(char opt, pthread_mutex_t *lock)
{
	static char	e;
	char		tmp;

	pthread_mutex_lock(lock);
	if (opt == 1)
		e = 1;
	tmp = e;
	pthread_mutex_unlock(lock);
	return (tmp);
}

int	check(int ms, t_philo *philo, int *ret)
{
	*ret = ft_usleep(ms, philo);
	return (*ret);
}

int	check_wait(t_philo *philo, int coordinates[2], int picked)
{
	int	ret;

	ret = wait_fork(philo, coordinates, picked);
	if (ret == 1)
		death(philo);
	if (ret == 2)
		free(philo);
	return (ret);
}

void	put_forks(t_philo *philo, int coordinates[2])
{
	pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
	philo->forks[coordinates[0]] = 'a';
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	philo->forks[coordinates[1]] = 'a';
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
}

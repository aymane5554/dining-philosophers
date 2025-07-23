/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:12:13 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/23 15:37:10 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	someone_died_waiting(const long long *args, long long *info,
			long long *philo_age, pthread_mutex_t *lock)
{
	int			j;

	j = 0;
	while (j < args[0])
	{
		if (timenow() - philo_age[j] > args[1] && philo_age[j] != 0)
		{
			end(1, lock + 1);
			info[0] = j + 1;
			info[2] = timenow() - args[5];
			pthread_mutex_unlock(lock);
			j = 0;
			while (j < args[0])
			{
				pthread_mutex_unlock(lock + 2 + j);
				j++;
			}
			return (1);
		}
		j++;
	}
	return (0);
}

void	join_and_destroy(const long long *args, pthread_t *threads,
			pthread_mutex_t *locks)
{
	int		i;

	i = 0;
	while (i < args[0])
		(pthread_join(threads[i], NULL), i++);
	i = 0;
	pthread_mutex_destroy(locks + 0);
	pthread_mutex_destroy(locks + 1);
	while (i < args[0])
		(pthread_mutex_destroy(locks + i), i++);
}

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

void	put_forks(t_philo *philo, int coordinates[2])
{
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
}

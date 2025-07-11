/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:12:13 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/11 11:21:47 by ayel-arr         ###   ########.fr       */
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

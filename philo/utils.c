/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:29:46 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/16 02:04:16 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_forks(pthread_mutex_t *lock, t_philo *philo, int	forks_index[2])
{
	pthread_mutex_lock(lock);
	if (philo->forks[forks_index[0]] == 'a'
		&& philo->forks[forks_index[1]] == 'a')
		return (pthread_mutex_unlock(lock), 1);
	pthread_mutex_unlock(lock);
	return (0);
}

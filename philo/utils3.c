/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:57:31 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/10 14:01:07 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	picking_forks(struct timeval *tv, t_philo *philo, int forks_index[2])
{
	if (philo->forks[forks_index[1]] == 'a')
	{
		philo->forks[forks_index[1]] = philo->number;
		printf("%lli %i has taken a fork\n",
			timestamp(tv, philo->lock + 2), philo->number + 1);
	}
	if (philo->forks[forks_index[0]] == 'a')
	{
		philo->forks[forks_index[0]] = philo->number;
		printf("%lli %i has taken a fork\n",
			timestamp(tv, philo->lock + 2), philo->number + 1);
	}
}

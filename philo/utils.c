/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:29:46 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/07 16:15:11 by ayel-arr         ###   ########.fr       */
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
	if (eating(philo, coordinates, meals))
		return (death(philo), 1);
	*picked_forks = 0;
	return (0);
}

t_philo	*create_philo_struct(char *forks, const long long *args,
		pthread_mutex_t *locks, long long *info)
{
	t_philo	*tmp;

	tmp = malloc(sizeof(t_philo));
	if (!tmp)
		return (NULL);
	tmp->args = args;
	tmp->forks = forks;
	tmp->lock = locks;
	tmp->info = info;
	return (tmp);
}

void	multiple_free(void *first, void *second, void *third, void *forth)
{
	free(first);
	free(second);
	free(third);
	free(forth);
}

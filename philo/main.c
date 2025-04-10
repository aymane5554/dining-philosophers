/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/10 10:45:16 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	life_death_circle(t_philo *philo, int forks_index[2])
{
	while (1)
	{
		pthread_mutex_lock(philo->lock + 1);
		if (check_forks2(philo, forks_index) == 1)
		{
			if (!eat_then_sleep(philo, forks_index, philo->lock))
				return (0);
		}
		else
			pthread_mutex_unlock(philo->lock + 1);
		if (think(philo, forks_index, philo->lock) == 1)
			return (0);
	}
	return (1);
}

int	life_death_circle2(t_philo *philo, int forks_index[2], int tmp)
{
	int	i;

	i = 0;
	while (i < tmp)
	{
		pthread_mutex_lock(philo->lock + 1);
		if (check_forks2(philo, forks_index) == 1)
		{
			if (!eat_then_sleep(philo, forks_index, philo->lock))
				return (0);
			i++;
		}
		else
			pthread_mutex_unlock(philo->lock + 1);
		if (think(philo, forks_index, philo->lock) == 1)
			return (0);
	}
	increment(philo, i);
	return (i);
}

void	*philosopher(void	*arg)
{
	t_philo				*philo;
	int					forks_index[2];
	int					tmp;

	philo = (t_philo *)arg;
	philo->age = timenow();
	if (philo->number == 0)
		forks_index[0] = philo->args[0] - 1;
	else
		forks_index[0] = philo->number - 1;
	forks_index[1] = philo->number;
	(pthread_mutex_lock(philo->lock), tmp = philo->args[4]);
	pthread_mutex_unlock(philo->lock);
	if (tmp < 1)
	{
		if (!life_death_circle(philo, forks_index))
			return (exit_thread(philo), NULL);
	}
	else
	{
		if (!life_death_circle2(philo, forks_index, tmp))
			return (exit_thread(philo), NULL);
	}
	return (exit_thread(philo), NULL);
}

void	check_death(long long *args, pthread_mutex_t *lock)
{
	int					tmp;

	while (1)
	{
		pthread_mutex_lock(lock);
		if (args[6] == args[0] || args[5] != 0)
		{
			pthread_mutex_unlock(lock);
			break ;
		}
		pthread_mutex_unlock(lock);
		usleep(100);
	}
	pthread_mutex_lock(lock);
	tmp = args[5];
	pthread_mutex_unlock(lock);
	if (tmp != 0)
		printf("%lli %i died\n",
			timestamp((struct timeval *)args[7], lock + 2), tmp);
}

//	args[0] = number_of_philosophers
//	args[1] = time_to_die
//	args[2] = time_to_eat
//	args[3] = time_to_sleep
//	args[4] = number_of_times_each_philosopher_must_eat
//			(optional)(1 if not specifed)
// 	args[5] = the dead philosopher
//	args[6] = The number of philosophers who have
//			finished eating (it equals 0 in the beginning)
// 	args[7] = time of death of a philosopher
//	(is a timeval pointer casted to long long)
//	locks[0] = mutex lock for args
//	locks[1] = mutex lock for forks
//	locks[2] = mutex lock for tv

int	main(int argc, char **argv)
{
	long long			*args;
	char				*forks;
	pthread_t			*threads;	
	struct timeval		tv;
	pthread_mutex_t		*locks;

	args = get_args(argc, argv);
	if (args == NULL)
		return (error(), 0);
	forks = malloc(args[0] * sizeof(char));
	threads = malloc(args[0] * sizeof(pthread_t));
	memset(forks, 'a', (args[0] * sizeof(char)));
	if (args[0] == 1)
		return (starving(threads, args, forks), 0);
	args[7] = (long long)&tv;
	locks = creating_locks();
	make_threads(threads, args, forks, locks);
	make_threads(threads, args, forks, locks);
	check_death(args, locks);
	return (finish(locks, args, forks, threads));
}

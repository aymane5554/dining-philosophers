/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/16 15:56:04 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	args[0] = number_of_philosophers
//	args[1] = time_to_die
//	args[2] = time_to_eat
//	args[3] = time_to_sleep
//	args[4] = number_of_times_each_philosopher_must_eat
//			(optional)(-1 if not specifed)
// 	info[0] = the dead philosopher
//	info[1] = The number of philosophers who have
//			finished eating (it equals 0 in the beginning)
// 	info[2] = time of death of a philosopher
//			(is a timeval pointer casted to long long)
//	locks[0]= mutex lock for info
//	locks[1]= mutex lock for end
//	locks[n]= mutex lock for forks

static t_philo	*philo_init(void *arg, int *meals, int coordinates[2])
{
	t_philo	*philo;

	*meals = 0;
	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->lock);
	*(philo->age) = timenow();
	pthread_mutex_unlock(philo->lock);
	coordinates[0] = philo->number - 1;
	if (philo->number == 0)
		coordinates[0] = philo->args[0] - 1;
	coordinates[1] = philo->number;
	return (philo);
}

void	*philosopher(void	*arg)
{
	t_philo	*philo;
	int		coordinates[2];
	int		meals;
	int		ret;

	philo = philo_init(arg, &meals, coordinates);
	while (meals != philo->args[4] && !end(0, philo->lock + 1))
	{
		if (philo->number % 2 == 0)
		{
			if (pick_forks(philo, coordinates))
				return (free(philo), NULL);
		}
		else
		{
			if (pick_forks_(philo, coordinates))
				return (free(philo), NULL);
		}
		ret = eating(philo, coordinates, &meals);
		if (ret == 1)
			return (death(philo), NULL);
		else if (ret == 2)
			return (free(philo), NULL);
	}
	return (free(philo), NULL);
}

static void	check_death(const long long *args, long long *philo_age,
			pthread_mutex_t *lock, long long *info)
{
	int			i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(lock);
		if (info[0] || info[1] == args[0])
		{
			pthread_mutex_unlock(lock);
			end(1, lock + 1);
			while (i < args[0])
				(pthread_mutex_unlock(lock + 2 + i), i++);
			break ;
		}
		if (someone_died_waiting(args, philo_age, lock))
			return ;
		pthread_mutex_unlock(lock);
		usleep(1000);
	}
	pthread_mutex_lock(lock);
	if (info[0])
		printf("%lld %lld died\n", info[2], info[0]);
	pthread_mutex_unlock(lock);
}

int	main(int argc, char **argv)
{
	const long long			*args;
	pthread_t				*threads;
	long long				*info;
	pthread_mutex_t			*locks;
	long long				*philos_age;

	if (!get_args_(argc, argv, (long long **)&args))
		return (0);
	philos_age = malloc(args[0] * sizeof(long long));
	if (!philos_age)
		return (free((void *)args), error(), 1);
	threads = malloc(args[0] * sizeof(pthread_t));
	if (!threads)
		return (error(), free(philos_age), free((long long *)args), 1);
	locks = creating_locks(args[0]);
	if (!locks)
		return (multiple_free((void *)args, threads, locks, philos_age), 1);
	info = make_threads(threads, (long long *)args, locks, philos_age);
	if (!info || usleep(50))
		return (multiple_free((void *)args, threads, locks, philos_age), 1);
	if (!make_threads(threads, (long long *)args, locks, philos_age))
		return (multiple_free((void *)args, threads, locks, philos_age), 1);
	check_death(args, philos_age, locks, info);
	(join_and_destroy(args, threads, locks), free((void *)args));
	return (multiple_free(threads, info, locks, philos_age), 0);
}

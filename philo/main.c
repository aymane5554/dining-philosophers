/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/27 13:20:22 by ayel-arr         ###   ########.fr       */
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
//	info[3] = time of start 
//	locks[0]= mutex lock for info
//	locks[1]= mutex lock for tv
//	locks[n]= mutex lock for forks

static t_philo	*philo_init(void *arg, int *meals,
			char *picked_forks, int coordinates[2])
{
	t_philo	*philo;

	*meals = 0;
	philo = (t_philo *)arg;
	philo->age = timenow();
	*picked_forks = 0;
	coordinates[0] = philo->number - 1;
	if (philo->number == 0)
		coordinates[0] = philo->args[0] - 1;
	coordinates[1] = philo->number;
	return (philo);
}

static void	*finish(t_philo	*philo)
{
	pthread_mutex_lock(philo->lock);
	philo->info[1]++;
	pthread_mutex_unlock(philo->lock);
	free(philo);
	return (NULL);
}

void	*philosopher(void	*arg)
{
	t_philo	*philo;
	int		coordinates[2];
	char	picked_forks;
	int		meals;
	int		picked;

	philo = philo_init(arg, &meals, &picked_forks, coordinates);
	while (meals != philo->args[4])
	{
		if (picked_forks == 0)
			picked_forks = pick_forks(philo, coordinates, &picked);
		if (picked_forks == 2)
		{
			if (start_eating(philo, &meals, &picked_forks, coordinates))
				return (NULL);
			continue ;
		}
		else
		{
			if (wait_fork(philo, coordinates, picked))
				return (death(philo));
			picked_forks = 2;
		}
	}
	return (finish(philo));
}

static void	check_death(const long long *args,
			pthread_mutex_t *lock, long long *info)
{
	while (1)
	{
		pthread_mutex_lock(lock);
		if (info[0] || info[1] == args[0])
			break ;
		pthread_mutex_unlock(lock);
		usleep(1000);
	}
	if (info[0])
		printf("%lld %lld died\n", info[2], info[0]);
}

int	main(int argc, char **argv)
{
	const long long			*args;
	char					*forks;
	pthread_t				*threads;
	long long				*info;
	pthread_mutex_t			*locks;

	args = get_args(argc, argv);
	if (args == NULL)
		return (error(), 0);
	forks = malloc(args[0] * sizeof(char));
	threads = malloc(args[0] * sizeof(pthread_t));
	memset(forks, 'a', (args[0] * sizeof(char)));
	if (args[0] == 1)
		return (starving(threads, args, forks), 0);
	locks = creating_locks(args[0]);
	info = make_threads(threads, args, forks, locks);
	usleep(50);
	make_threads(threads, args, forks, locks);
	check_death(args, locks, info);
	return (0);
}

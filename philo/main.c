/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/25 10:18:24 by ayel-arr         ###   ########.fr       */
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

int	wait_forks(t_philo *philo, int coordinates[2])
{
	int		count;
	char	p;

	count = 0;
	p = 0;
	while (timenow() - philo->age < philo->args[1])
	{
		pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
		if (philo->forks[coordinates[0]] == 'a')
		{
			philo->forks[coordinates[0]] = 'u';
			count++;
			p = 1;
		}
		pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
		if (p)
		{
			pthread_mutex_lock(philo->lock);
			printf("%lld %d has taken a fork\n", timenow() - philo->info[3], philo->number + 1);
			pthread_mutex_unlock(philo->lock);
			p = 0;
		}
		pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
		if (philo->forks[coordinates[1]] == 'a')
		{
			philo->forks[coordinates[1]] = 'u';
			count++;
			p = 1;
		}
		pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
		if (p)
		{
			pthread_mutex_lock(philo->lock);
			printf("%lld %d has taken a fork\n", timenow() - philo->info[3], philo->number + 1);
			pthread_mutex_unlock(philo->lock);
			p = 0;
		}
		if (count == 2)
			return (0);
		usleep(100);
	}
	return (1);
}

int	wait_fork(t_philo *philo, int coordinates[2], int picked)
{
	int	fork_needed;

	pthread_mutex_lock(philo->lock);
	printf("%lld %d is thinking\n", timenow() - philo->info[3], philo->number + 1);
	pthread_mutex_unlock(philo->lock);
	if (picked == -1)
	{
		if (wait_forks(philo, coordinates))
			return (1);
		return (0);
	}
	if (picked == coordinates[0])
		fork_needed = coordinates[1];
	if (picked == coordinates[1])
		fork_needed = coordinates[0];
	while (timenow() - philo->age < philo->args[1])
	{
		pthread_mutex_lock(philo->lock + 2 + fork_needed);
		if (philo->forks[fork_needed] == 'a')
		{
			philo->forks[fork_needed] = 'u';
			pthread_mutex_unlock(philo->lock + 2 + fork_needed);
			pthread_mutex_lock(philo->lock);
			printf("%lld %d has taken a fork\n", timenow() - philo->info[3], philo->number + 1);
			pthread_mutex_unlock(philo->lock);
			return (0);
		}
		pthread_mutex_unlock(philo->lock + 2 + fork_needed);
		usleep(100);
	}
	return (1);
}

int	eating(t_philo *philo, int coordinates[2])
{
	pthread_mutex_lock(philo->lock);
	printf("%lld %d is eating\n", timenow() - philo->info[3], philo->number + 1);
	pthread_mutex_unlock(philo->lock);
	philo->age = timenow();
	if (ft_usleep(philo->args[2], philo->args[1], philo->age))
		return (1);
	pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
	philo->forks[coordinates[0]] = 'a';
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	philo->forks[coordinates[1]] = 'a';
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
	pthread_mutex_lock(philo->lock);
	printf("%lld %d is sleeping\n", timenow() - philo->info[3], philo->number + 1);
	pthread_mutex_unlock(philo->lock);
	if (ft_usleep(philo->args[3], philo->args[1], philo->age))
		return (1);
	return (0);
}

char	pick_forks(t_philo *philo, int coordinates[2], int	*picked)
{
	char	picked_forks;
	int		tmp;

	picked_forks = 0;
	*picked = -1;
	pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
	if (philo->forks[coordinates[0]] == 'a')
	{
		philo->forks[coordinates[0]] = 'u';
		tmp = coordinates[0];
		picked_forks++;
	}
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
	if (picked_forks)
	{
		pthread_mutex_lock(philo->lock);
		printf("%lld %d has taken a fork\n", timenow() - philo->info[3], philo->number + 1);
		pthread_mutex_unlock(philo->lock);
	}
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	if (philo->forks[coordinates[1]] == 'a')
	{
		philo->forks[coordinates[1]] = 'u';
		tmp = coordinates[1];
		picked_forks++;
	}
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
	if (picked_forks == 2 || tmp == coordinates[1])
	{
		pthread_mutex_lock(philo->lock);
		printf("%lld %d has taken a fork\n", timenow() - philo->info[3], philo->number + 1);
		pthread_mutex_unlock(philo->lock);
	}
	if (picked_forks == 1)
		*picked = tmp;
	return (picked_forks);
}

void	*philosopher(void	*arg)
{
	t_philo	*philo;
	int		coordinates[2];
	char	picked_forks;
	int		meals;
	int		picked;

	meals = 0;
	philo = (t_philo *)arg;
	philo->age = timenow();
	picked_forks = 0;
	coordinates[0] = philo->number - 1;
	if (philo->number == 0)
		coordinates[0] = philo->args[0] - 1;
	coordinates[1] = philo->number;
	while (meals != philo->args[4])
	{
		if (picked_forks == 0)
			picked_forks = pick_forks(philo, coordinates, &picked);
		if (picked_forks == 2)
		{
			if (eating(philo, coordinates))
			{
				pthread_mutex_lock(philo->lock);
				philo->info[0] = philo->number + 1;
				philo->info[2] = timenow() - philo->info[3];
				pthread_mutex_unlock(philo->lock);
				free(philo);
				return (NULL);
			}
			if (philo->args[4] != -1)
				meals++;
			picked_forks = 0;
			continue ;
		}
		else
		{
			if (wait_fork(philo, coordinates, picked))
			{
				pthread_mutex_lock(philo->lock);
				philo->info[0] = philo->number + 1;
				philo->info[2] = timenow() - philo->info[3];
				pthread_mutex_unlock(philo->lock);
				free(philo);
				return (NULL);
			}
			picked_forks = 2;
		}
	}
	pthread_mutex_lock(philo->lock);
	philo->info[1]++;
	pthread_mutex_unlock(philo->lock);
	return (NULL);
}

void	check_death(const long long *args,
			pthread_mutex_t *lock, long long *info)
{
	pthread_mutex_lock(lock);
	while (!info[0] && info[1] != args[0])
	{
		pthread_mutex_unlock(lock);
		usleep(100);
		pthread_mutex_lock(lock);
	}
	if (info[0])
		printf("%lld %lld died\n", info[2], info[0]);
	free(info);
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

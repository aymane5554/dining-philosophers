/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/05/29 16:20:06 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	args[0] = number_of_philosophers
//	args[1] = time_to_die
//	args[2] = time_to_eat
//	args[3] = time_to_sleep
//	args[4] = number_of_times_each_philosopher_must_eat
//			(optional)(-1 if not specifed)
// 	args[5] = the dead philosopher
//	args[6] = The number of philosophers who have
//			finished eating (it equals 0 in the beginning)
// 	args[7] = time of death of a philosopher
//	(is a timeval pointer casted to long long)
//	locks[0] = mutex lock for args
//	locks[1] = mutex lock for tv
//	locks[n] = mutex lock for forks

int	wait_forks(t_philo *philo, int coordinates[2])
{
	int	count;

	count = 0;
	while (philo->age - timenow() < philo->args[1])
	{
		if (philo->forks[coordinates[0]] == 'a')
		{
			pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
			philo->forks[coordinates[0]] = 'u';
			pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
			count++;
		}
		if (philo->forks[coordinates[1]] == 'a')
		{
			pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
			philo->forks[coordinates[1]] = 'u';
			pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
			count++;
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
	while (philo->age - timenow() < philo->args[1])
	{
		if (philo->forks[fork_needed] == 'a')
		{
			pthread_mutex_lock(philo->lock + 2 + fork_needed);
			philo->forks[fork_needed] = 'u';
			pthread_mutex_unlock(philo->lock + 2 + fork_needed);
		}
		usleep(100);
	}
	return (0);
}

int	eating(t_philo *philo, int coordinates[2])
{
	philo->age = timenow();
	if (ft_usleep(philo->args[2], philo->args[1], philo->age))
		return (1);
	pthread_mutex_lock(philo->lock + 2 + coordinates[0]);
	philo->forks[coordinates[0]] = 'a';
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	philo->forks[coordinates[1]] = 'a';
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
	if (ft_usleep(philo->args[3], philo->args[1], philo->age))
		return (1);
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
		philo->forks = 'u';
		tmp = coordinates[0];
		picked_forks++;
	}
	pthread_mutex_unlock(philo->lock + 2 + coordinates[0]);
	pthread_mutex_lock(philo->lock + 2 + coordinates[1]);
	if (philo->forks[coordinates[1]] == 'a')
	{
		philo->forks = 'u';
		tmp = coordinates[1];
		picked_forks++;
	}
	pthread_mutex_unlock(philo->lock + 2 + coordinates[1]);
	if (picked && pick_forks == 1)
		*picked = tmp;
	return (pick_forks);
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
				return (NULL); // free leaks
			if (philo->args[4] != -1)
				meals++;
			picked_forks = 0;
			continue ;
		}
		else
		{
			if (wait_fork(philo, coordinates, picked))
				return (NULL);
			picked_forks = 2;
		}
	}
	return (NULL);
}

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
	locks = creating_locks(args[0]);
	make_threads(threads, args, forks, locks);
	make_threads(threads, args, forks, locks);
	return (0);
}

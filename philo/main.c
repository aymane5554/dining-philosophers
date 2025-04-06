/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/06 19:09:01 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	die(t_philo	*philo, int forks_index[2], pthread_mutex_t *lock)
{
	struct timeval		tv;
	int					tmp;

	pthread_mutex_lock(lock);
	tmp = philo->args[1];
	pthread_mutex_unlock(lock);
	gettimeofday(&tv, NULL);
	printf("%lli %i is thinking\n", timestamp(&tv, lock + 2), philo->number + 1);
	while (!check_forks(lock, philo, forks_index))
	{
		gettimeofday(&tv, NULL);
		if (((tv.tv_sec * 1000) + tv.tv_usec / 1000) - philo->age
		> tmp)
		{
			pthread_mutex_lock(lock);
			gettimeofday((struct timeval *)philo->args[7], NULL);
			philo->args[5] = philo->number + 1;
			pthread_mutex_unlock(lock);
			return (1);
		}
		usleep(100);
	}
	return (0);
}

void	eat_then_sleep(t_philo	*philo, int forks_index[2],
		pthread_mutex_t *lock)
{
	struct timeval		tv;
	int					arg;

	gettimeofday(&tv, NULL);
	printf("%lli %i has taken a fork\n",
		timestamp(&tv, lock + 2), philo->number + 1);
	printf("%lli %i has taken a fork\n",
		timestamp(&tv, lock + 2), philo->number + 1);
	philo->forks[forks_index[1]] = 'u';
	philo->forks[forks_index[0]] = 'u';
	printf("%lli %i is eating\n", timestamp(&tv, lock + 2), philo->number + 1);
	arg = philo->args[2];
	pthread_mutex_unlock(lock + 1);
	philo->age = timenow();
	usleep(arg * 1000);
	pthread_mutex_lock(lock + 1);
	philo->forks[forks_index[1]] = 'a';
	philo->forks[forks_index[0]] = 'a';
	pthread_mutex_unlock(lock + 1);
	pthread_mutex_lock(lock);
	arg = philo->args[3];
	(pthread_mutex_unlock(lock), gettimeofday(&tv, NULL));
	printf("%lli %i is sleeping\n", timestamp(&tv, lock + 2), philo->number + 1);
	usleep(arg * 1000);
}

void	life_death_circle(t_philo *philo, int forks_index[2])
{
	while (1)
	{
		pthread_mutex_lock(philo->lock + 1);
		if (check_forks2(philo, forks_index) == 1)
			eat_then_sleep(philo, forks_index, philo->lock);
		else
			pthread_mutex_unlock(philo->lock + 1);
		if (die(philo, forks_index, philo->lock) == 1)
			break ;
	}
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
			eat_then_sleep(philo, forks_index, philo->lock);
			i++;
		}
		else
			pthread_mutex_unlock(philo->lock + 1);
		if (die(philo, forks_index, philo->lock) == 1)
			break ;
	}
	return (i);
}

void	*philosopher(void	*arg)
{
	t_philo				*philo;
	int					forks_index[2];
	pthread_mutex_t		*lock;
	int					tmp;
	int					i;

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
		life_death_circle(philo, forks_index);
	else
	{
		i = life_death_circle2(philo, forks_index, tmp);
		increment(philo, i);
	}
	(lock = philo->lock, pthread_mutex_lock(lock));
	return (free(arg), pthread_mutex_unlock(lock), NULL);
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
//  locks[0] = mutex lock for args
//  locks[1] = mutex lock for forks
//  locks[2] = mutex lock for tv

// TODO: 
//      infinte eating : IDK

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
		return (dying(threads, args, forks), 0);
	args[7] = (long long)&tv;
	locks = creating_locks();
	make_threads(threads, args, forks, locks);
	make_threads(threads, args, forks, locks);
	check_death(args, locks);
	return (finish(locks, args, forks, threads));
}

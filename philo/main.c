/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/17 23:25:14 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	die(t_philo	*philo, int forks_index[2], pthread_mutex_t *lock)
{
	suseconds_t			last_time;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	last_time = (tv.tv_sec * 1000000) + tv.tv_usec;
	while (!check_forks(lock, philo, forks_index))
	{
		gettimeofday(&tv, NULL);
		if (((tv.tv_sec * 1000000) + tv.tv_usec) - last_time
			> philo->args[1] * 1000)
		{
			printf("%li %i died\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000),
				philo->number + 1); 
			pthread_mutex_lock(lock);
			philo->args[5]--;
			pthread_mutex_unlock(lock);
			return (1);
		}
	}
	return (0);
}

void	eat_then_sleep(t_philo	*philo, int forks_index[2],
		pthread_mutex_t *lock)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	printf("%li %i has taken a fork\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000),
		philo->number + 1);
	pthread_mutex_lock(lock);
	philo->forks[forks_index[1]] = 'u';
	philo->forks[forks_index[0]] = 'u';
	pthread_mutex_unlock(lock);
	printf("%li %i is eating\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000),
		philo->number + 1);
	usleep(philo->args[2] * 1000);
	pthread_mutex_lock(lock);
	philo->forks[forks_index[1]] = 'a';
	philo->forks[forks_index[0]] = 'a';
	pthread_mutex_unlock(lock);
	printf("%li %i is sleeping\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000),
		philo->number + 1);
	usleep(philo->args[3] * 1000);
	printf("%li %i is thinking\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000),
		philo->number + 1);
}

void	*philosopher(void	*arg)
{
	t_philo				*philo;
	int					forks_index[2];
	int					i;

	philo = (t_philo *)arg;
	if (philo->number == 0)
		forks_index[0] = philo->args[0] - 1;
	else
		forks_index[0] = philo->number - 1;
	forks_index[1] = philo->number;
	i = 0;
	while (i < philo->args[4])
	{
		if (check_forks(philo->lock, philo, forks_index) == 1)
		{
			eat_then_sleep(philo, forks_index, philo->lock);
			i++;
		}
		if (die(philo, forks_index, philo->lock) == 1)
			break ;
	}
	if (i == philo->args[4])
	{
		pthread_mutex_lock(philo->lock);
		philo->args[6]++;
		pthread_mutex_unlock(philo->lock);
	}
	return (free(arg), NULL);
}

//	args[0] = number_of_philosophers
//	args[1] = time_to_die
//	args[2] = time_to_eat
//	args[3] = time_to_sleep
//	args[4] = number_of_times_each_philosopher_must_eat
//			(optional)(1 if not specifed)
// 	args[5] = number_of_philosophers_alive
//	args[6] = The number of philosophers who have
//			finished eating (it equals 0 in the beginning)

int	main(int argc, char **argv)
{
	int					*args;
	char				*forks;
	pthread_t			*threads;
	pthread_mutex_t		lock;

	pthread_mutex_init(&lock, NULL);
	args = get_args(argc, argv);
	if (args == NULL)
		return (error(), 0);
	forks = malloc(args[0] * sizeof(char));
	threads = malloc(args[0] * sizeof(pthread_t));
	memset(forks, 'a', (args[0] * sizeof(char)));
	if (args[0] == 1)
		return (dying_alone(threads, args, forks), 0);
	make_threads(threads, args, forks, &lock);
	usleep(1000);
	make_threads(threads, args, forks, &lock);
	return (free(args), free(forks), 0);
}

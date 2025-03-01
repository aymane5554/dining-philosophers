/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/01 15:31:26 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*first_philosopher(void	*arg)
{
	t_philo				*philo;
	pthread_mutex_t		lock;

	pthread_mutex_init(&lock, NULL);
	philo = (t_philo *)arg;
	if (philo->forks[philo->args[0] - 1] == 'a'
		&& philo->forks[philo->number] == 'a')
	{
		printf("%i is eating\n", philo->number);
		pthread_mutex_lock(&lock);
		philo->forks[philo->args[0] - 1] = 'u';
		philo->forks[philo->number] = 'u';
		pthread_mutex_unlock(&lock);
		usleep(philo->args[2] * 1000);
		pthread_mutex_lock(&lock);
		philo->forks[philo->args[0] - 1] = 'a';
		philo->forks[philo->number] = 'a';
		pthread_mutex_unlock(&lock);
		printf("%i is sleeping\n", philo->number);
	}
	free(arg);
	return (NULL);
}

void	*last_philosopher(void	*arg)
{
	t_philo				*philo;
	pthread_mutex_t		lock;

	philo = (t_philo *)arg;
	pthread_mutex_init(&lock, NULL);
	if (philo->number == philo->args[0] && philo->forks[0] == 'a'
		&& philo->forks[philo->number - 2] == 'a')
	{
		printf("%i is eating\n", philo->number);
		pthread_mutex_lock(&lock);
		philo->forks[0] = 'u';
		philo->forks[philo->number - 2] = 'u';
		pthread_mutex_unlock(&lock);
		usleep(philo->args[2] * 1000);
		pthread_mutex_lock(&lock);
		philo->forks[0] = 'a';
		philo->forks[philo->number - 2] = 'a';
		pthread_mutex_unlock(&lock);
		printf("%i is sleeping\n", philo->number);
	}
	free(arg);
	return (NULL);
}

void	*philosopher(void	*arg)
{
	t_philo				*philo;
	pthread_mutex_t		lock;

	philo = (t_philo *)arg;
	pthread_mutex_init(&lock, NULL);
	if (philo->number != philo->args[0] && philo->number != 1
		&& philo->forks[philo->number - 2] == 'a'
		&& philo->forks[philo->number] == 'a')
	{
		printf("%i is eating\n", philo->number);
		philo->forks[philo->number - 2] = 'u';
		philo->forks[philo->number] = 'u';
		pthread_mutex_unlock(&lock);
		usleep(philo->args[2] * 1000);
		pthread_mutex_lock(&lock);
		philo->forks[philo->number - 2] = 'a';
		philo->forks[philo->number] = 'a';
		pthread_mutex_unlock(&lock);
		printf("%i is sleeping\n", philo->number);
	}
	free(arg);
	return (NULL);
}

void	death_check(int *args)
{
	while (args[5] == args[0] && args[4] != 0)
		continue ;
}

//	args[0] = number_of_philosophers
//	args[1] = time_to_die
//	args[2] = time_to_eat
//	args[3] = time_to_sleep
//	args[4] = number_of_times_each_philosopher_must_ea
//			(optional)(-1 if not specifed)
// 	args[5] = number_of_philosophers_alive

int	main(int argc, char **argv)
{
	int			*args;
	char		*forks;
	pthread_t	*threads;
	t_philo		*tmp;
	int			i;

	i = 0;
	args = get_args(argc, argv);
	if (args == NULL)
		return (error(), 0);
	forks = malloc(args[0] * sizeof(char));
	threads = malloc(args[0] * sizeof(pthread_t));
	memset(forks, 'a', (args[0] * sizeof(char)));
	while (i < args[0])
	{
		tmp = malloc(sizeof(t_philo));
		tmp->args = args;
		tmp->forks = forks;
		tmp->number = i + 1;
		if (i == 0)
			pthread_create(threads + i, NULL, first_philosopher, tmp);
		else if (i == args[0] - 1)
			pthread_create(threads + i, NULL, last_philosopher, tmp);
		else
			pthread_create(threads + i, NULL, philosopher, tmp);
		i++;
	}
	return (death_check(args), free(args), free(forks), 0);
}

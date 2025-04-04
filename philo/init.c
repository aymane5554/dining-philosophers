/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/04 10:19:42 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	*get_args(int argc, char **argv)
{
	long long	*args;
	int			i;
	int			j;

	if (argc < 5 || argc > 6)
		return (NULL);
	args = malloc(8 * sizeof(long long));
	if (args == NULL)
		return (NULL);
	i = 1;
	j = 0;
	while (i < argc)
	{
		args[j] = (long long)ft_atoi(argv[i]);
		if (args[j] == -1)
			return (free(args), NULL);
		i++;
		j++;
	}
	if (argc == 5)
		args[4] = 1;
	args[5] = 0;
	args[6] = 0;
	args[7] = 0;
	return (args);
}

void	error(void)
{
	write(2, "error\n", 6);
}

pthread_mutex_t	*creating_locks(void)
{
	pthread_mutex_t	*locks;

	locks = malloc(3 * sizeof(pthread_mutex_t));
	pthread_mutex_init(locks, NULL);
	pthread_mutex_init(locks + 1, NULL);
	pthread_mutex_init(locks + 2, NULL);
	return (locks);
}

void	make_threads(pthread_t	*threads, long long *args,
		char *forks, pthread_mutex_t	*locks)
{
	int							i;
	t_philo						*tmp;
	static int					j;

	i = j;
	while (i < args[0])
	{
		tmp = malloc(sizeof(t_philo));
		tmp->args = args;
		tmp->forks = forks;
		tmp->number = i;
		tmp->lock = locks;
		pthread_create(threads + i, NULL, philosopher, tmp);
		pthread_detach(threads[i]);
		i += 2;
	}
	j = 1;
	return ;
}

long long	timenow(void)
{
	struct timeval		tv;
	long long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

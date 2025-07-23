/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/23 15:45:27 by ayel-arr         ###   ########.fr       */
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
	args = malloc(6 * sizeof(long long));
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
		args[4] = -1;
	return (args);
}

void	error(void)
{
	write(2, "error\n", 6);
}

pthread_mutex_t	*creating_locks(int no_philos)
{
	pthread_mutex_t	*locks;
	int				i;

	i = 0;
	locks = malloc((no_philos + 2) * sizeof(pthread_mutex_t));
	if (!locks)
		return (NULL);
	if (pthread_mutex_init(locks, NULL))
		return (NULL);
	if (pthread_mutex_init(locks + 1, NULL))
		return (NULL);
	while (i < no_philos)
	{
		if (pthread_mutex_init(locks + 2 + i, NULL))
			return (NULL);
		i++;
	}
	return (locks);
}

long long	*make_threads(pthread_t	*threads, long long *args,
		pthread_mutex_t	*locks, long long *philo_age)
{
	t_philo		**tmp;
	int			i;
	long long	*info;

	i = 0;
	info = malloc(3 * sizeof(long long));
	if (!info)
		return (NULL);
	memset(info, 0, 3 * sizeof(long long));
	args[5] = timenow();
	tmp = create_philo_struct(args, locks, info, philo_age);
	if (!tmp)
		return (free(info), NULL);
	while (i < args[0])
	{
		if (pthread_create(threads + i, NULL, philosopher, tmp[i]) != 0)
			return (end(1, locks + 1), unlock_all(locks, args[0]),
				join_and_destroy(args, threads, locks),
				free(tmp), free(info), NULL);
		i++;
	}
	free(tmp);
	return (info);
}

long long	timenow(void)
{
	struct timeval		tv;
	long long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

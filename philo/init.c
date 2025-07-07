/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/07 15:45:51 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	*get_args(int argc, char **argv)
{
	long long	*args;
	int			i;
	int			j;

	if (argc < 5 || argc > 6)
		return (error(), NULL);
	args = malloc(5 * sizeof(long long));
	if (args == NULL)
		return (error(), NULL);
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
	pthread_mutex_init(locks, NULL);
	pthread_mutex_init(locks + 1, NULL);
	while (i < no_philos)
	{
		pthread_mutex_init(locks + 2 + i, NULL);
		i++;
	}
	return (locks);
}

long long	*make_threads(pthread_t	*threads, const long long *args,
		char *forks, pthread_mutex_t	*locks)
{
	int					i;
	t_philo				*tmp;
	static int			j;
	static long long	*info;

	i = j;
	if (!info)
	{
		info = malloc(4 * sizeof(long long));
		if (!info)
			return (NULL);
		(memset(info, 0, 4 * sizeof(long long)), info[3] = timenow());
	}
	while (i < args[0])
	{
		tmp = create_philo_struct(forks, args, locks, info);
		if (!tmp)
			return (free(info), NULL);
		tmp->number = i;
		if (pthread_create(threads + i, NULL, philosopher, tmp) != 0)
			return (free(tmp), free(info), NULL);
		pthread_detach(threads[i]);
		i += 2;
	}
	return (j = 1, info);
}

long long	timenow(void)
{
	struct timeval		tv;
	long long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

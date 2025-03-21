/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/21 21:48:54 by ayel-arr         ###   ########.fr       */
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

pthread_mutex_t	*make_threads(pthread_t	*threads, long long *args, char *forks)
{
	int							i;
	t_philo						*tmp;
	static int					j;
	static pthread_mutex_t		lock;

	i = j;
	if (i == 0)
		pthread_mutex_init(&lock, NULL);
	while (i < args[0])
	{
		tmp = malloc(sizeof(t_philo));
		tmp->args = args;
		tmp->forks = forks;
		tmp->number = i;
		tmp->lock = &lock;
		pthread_create(threads + i, NULL, philosopher, tmp);
		pthread_detach(threads[i]);
		i += 2;
	}
	j = 1;
	return (&lock);
}

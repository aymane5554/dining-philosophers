/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/13 17:50:13 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*get_args(int argc, char **argv)
{
	int	*args;
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (NULL);
	args = malloc(7 * sizeof(int));
	if (args == NULL)
		return (NULL);
	i = 1;
	j = 0;
	while (i < argc)
	{
		args[j] = ft_atoi(argv[i]);
		if (args[j] == -1)
			return (free(args), NULL);
		i++;
		j++;
	}
	if (argc == 6)
		args[4] = 1;
	args[5] = args[0];
	args[6] = 0;
	return (args);
}

void	error(void)
{
	write(2, "error\n", 6);
}

void	make_threads(pthread_t	*threads, int *args, char *forks, char j)
{
	int			i;
	t_philo		*tmp;

	i = j;
	while (i < args[0])
	{
		tmp = malloc(sizeof(t_philo));
		tmp->args = args;
		tmp->forks = forks;
		tmp->number = i;
		pthread_create(&threads[i], NULL, philosopher, tmp);
		i += 2;
	}
}

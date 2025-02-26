/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/26 15:58:25 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void	*arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	printf("num = %i\n", philo->number);
	free(arg);
	return (NULL);
}

//	args[0] = number_of_philosophers
//	args[1] = time_to_die
//	args[2] = time_to_eat
//	args[3] = time_to_sleep
//	args[4] = number_of_times_each_philosopher_must_eat (optional)

// TODO:
//      add a function to check if one of the philosophers is dead

int	main(int argc, char **argv)
{
	int			*args;
	char		*forks;
	pthread_t	thread;
	t_philo		*tmp;
	int			i;

	i = 0;
	args = get_args(argc, argv);
	if (args == NULL)
		return (error(), 0);
	forks = malloc(args[0] * sizeof(char));
	memset(forks, 'a', (args[0] * sizeof(char)));
	while (i < args[0])
	{
		tmp = malloc(sizeof(t_philo));
		tmp->args = args;
		tmp->forks = forks;
		tmp->number = i + 1;
		pthread_create(&thread, NULL, philosopher, tmp);
		i++;
	}
	pthread_join(thread, NULL);
	(free(args), free(forks));
	return (0);
}

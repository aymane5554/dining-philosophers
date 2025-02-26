/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/02/26 15:01:07 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void	*arg)
{
	void	**aarg;
	int		*args;

	aarg = (void **)arg;
	args = (int *)aarg[1];
	if ((size_t)aarg[2] == (size_t)args[0])
		printf("last philo\n");
	if ((size_t)aarg[2] == 0)
		printf("first philo\n");
	return (NULL);
}

//	args[0] = number_of_philosophers
//	args[1] = time_to_die
//	args[2] = time_to_eat
//	args[3] = time_to_sleep
//	args[4] = number_of_times_each_philosopher_must_eat (optional)

int	main(int argc, char **argv)
{
	int			*args;
	char		*forks;
	void		*arg[3];
	pthread_t	thread;

	args = get_args(argc, argv);
	if (args == NULL)
		return (error(), 0);
	forks = malloc(args[0] * sizeof(char));
	memset(forks, 'a', (args[0] * sizeof(char)));	
	arg[0] = forks;
	arg[1] = args;
	arg[2] = (void *)0;
	pthread_create(&thread, NULL, philosopher, arg);
	pthread_join(thread, NULL);
	(free(args), free(forks));
	return (0);
}

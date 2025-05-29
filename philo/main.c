/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:29 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/05/29 14:41:07 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	args[0] = number_of_philosophers
//	args[1] = time_to_die
//	args[2] = time_to_eat
//	args[3] = time_to_sleep
//	args[4] = number_of_times_each_philosopher_must_eat
//			(optional)(-1 if not specifed)
// 	args[5] = the dead philosopher
//	args[6] = The number of philosophers who have
//			finished eating (it equals 0 in the beginning)
// 	args[7] = time of death of a philosopher
//	(is a timeval pointer casted to long long)
//	locks[0] = mutex lock for args
//	locks[1] = mutex lock for tv
//	locks[n] = mutex lock for forks

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
		return (starving(threads, args, forks), 0);
	args[7] = (long long)&tv;
	locks = creating_locks(args[0]);
	return (0);
}

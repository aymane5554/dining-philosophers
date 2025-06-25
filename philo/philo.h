/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:25:01 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/17 12:10:09 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	char					*forks;
	const long long			*args;
	int						number;
	long long				age;
	long long				*info;
	pthread_mutex_t			*lock;
}	t_philo;

int					ft_atoi(const char *ptr);
long long			*get_args(int argc, char **argv);
void				error(void);
long long			*make_threads(pthread_t	*threads, const long long *args,
						char *forks, pthread_mutex_t	*locks);
void				*philosopher(void	*arg);
void				starving(pthread_t *threads,
						const long long *args, char *forks);
long long			timestamp(struct timeval *arg_tv, pthread_mutex_t *lock);
pthread_mutex_t		*creating_locks(int no_philos);
long long			timenow(void);
int					ft_usleep(int ms, int time2die, long long last_meal);
#endif
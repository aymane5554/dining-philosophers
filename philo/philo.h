/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:25:01 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/24 03:32:14 by ayel-arr         ###   ########.fr       */
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

int					ft_atoi(const char *ptr);
long long			*get_args(int argc, char **argv);
void				error(void);
void				make_threads(pthread_t	*threads, long long *args, char *forks, pthread_mutex_t	*locks);
void				*philosopher(void	*arg);

typedef struct s_philo
{
	char				*forks;
	long long			*args;
	int					number;
	long long			age;
	pthread_mutex_t		*lock;
}	t_philo;

int				check_forks(pthread_mutex_t *lock, t_philo *philo, int forks_index[2]);
void			dying_alone(pthread_t *threads, long long *args, char *forks);
int				finish(pthread_mutex_t *lock, long long *args, char *forks,
					pthread_t *threads);
long long		timestamp(struct timeval *arg_tv, pthread_mutex_t *lock);
void			increment(t_philo *philo, int i);
pthread_mutex_t	*creating_locks(void);
long long 		timenow(void);

#endif
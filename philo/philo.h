/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:25:01 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/17 17:11:02 by ayel-arr         ###   ########.fr       */
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
	const long long	*args;
	long long		*age;
	long long		*info;
	pthread_mutex_t	*lock;
	int				number;
}	t_philo;

void				*death(t_philo *philo);
int					eating(t_philo *philo, int coordinates[2], int *meals);
char				pick_forks(t_philo *philo, int coordinates[2]);
char				pick_forks_(t_philo *philo, int coordinates[2]);
int					ft_atoi(const char *ptr);
long long			*get_args(int argc, char **argv);
long long			*get_args_(int argc, char **argv, long long **args);
void				error(void);
long long			*make_threads(pthread_t	*threads, long long *args,
						pthread_mutex_t	*locks, long long *philo_age);
void				*philosopher(void	*arg);
void				starving(const long long *args);
pthread_mutex_t		*creating_locks(int no_philos);
long long			timenow(void);
int					ft_usleep(int ms, t_philo *philo);
t_philo				**create_philo_struct(const long long *args,
						pthread_mutex_t *locks, long long *info,
						long long *philo_age);
void				multiple_free(void *first, void *second,
						void *third, void *forth);
char				end(char opt, pthread_mutex_t *lock);
void				put_forks(t_philo *philo, int coordinates[2]);
void				put_forks_(t_philo *philo, int coordinates[2]);
int					check(int ms, t_philo *philo, int *ret);
void				join_and_destroy(const long long *args, pthread_t *threads,
						pthread_mutex_t *locks);
char				someone_died_waiting(const long long *args, long long *info,
						long long *philo_age, pthread_mutex_t *lock);
void				unlock_all(pthread_mutex_t *locks, int n);
#endif

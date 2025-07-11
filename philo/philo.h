/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:25:01 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/11 15:00:35 by ayel-arr         ###   ########.fr       */
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
	char			*forks;
	const long long	*args;
	long long		age;
	long long		*info;
	pthread_mutex_t	*lock;
	int				number;
}	t_philo;

int					start_eating(t_philo *philo, int *meals,
						char *picked_forks, int coordinates[2]);
void				*death(t_philo *philo);
int					wait_fork(t_philo *philo, int coordinates[2], int picked);
int					eating(t_philo *philo, int coordinates[2], int *meals);
char				pick_forks(t_philo *philo,
						int coordinates[2], int	*picked);
int					ft_atoi(const char *ptr);
long long			*get_args(int argc, char **argv);
long long			*get_args_(int argc, char **argv, long long **args);
void				error(void);
long long			*make_threads(pthread_t	*threads, const long long *args,
						char *forks, pthread_mutex_t	*locks);
void				*philosopher(void	*arg);
void				starving(const long long *args);
pthread_mutex_t		*creating_locks(int no_philos);
long long			timenow(void);
int					ft_usleep(int ms, t_philo *philo);
t_philo				*create_philo_struct(char *forks, const long long *args,
						pthread_mutex_t *locks, long long *info);
void				multiple_free(void *first, void *second,
						void *third, void *forth);
char				end(char opt, pthread_mutex_t *lock);
int					check_wait(t_philo *philo, int coordinates[2], int picked);
int					check(int ms, t_philo *philo, int *ret);
void				put_forks(t_philo *philo, int coordinates[2]);
#endif

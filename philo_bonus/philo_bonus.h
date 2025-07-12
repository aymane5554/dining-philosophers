/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:37:56 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/12 10:40:34 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <wait.h>
# include <signal.h>

typedef struct s_arg
{
	int			args[5];
	sem_t		*sem_ate;
	char		ate[1];
	sem_t		*sem;
	sem_t		*end;
	long long	age;
	int			number;
}	t_arg;

int			get_args(int argc, char **argv, int *args);
int			ft_atoi(const char *ptr);
long long	timenow(void);
long long	start_time(void);
void		error(void);
int			ft_usleep(int ms, int time2die, long long last_meal, t_arg *arg);
void		kill_philos(pid_t *pids, sem_t *sem);
void		check_fork(int i, pid_t *pids, sem_t *sem, t_arg *arg);
int			philosopher(t_arg *arg);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_itoa(int n);
char		*get_sem_name(int number);
void		pick_forks(t_arg *arg);
void		msg(char opt, int n, sem_t *end);
#endif
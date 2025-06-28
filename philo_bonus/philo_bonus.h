/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:37:56 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/28 15:42:51 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <wait.h>

typedef struct s_arg
{
	int			*args;
	sem_t		*sem_ate;
	char		*ate;
	long long	age;
	int			number;
	sem_t		*sem;
}	t_arg;

int			*get_args(int argc, char **argv);
int			ft_atoi(const char *ptr);
long long	timenow(void);
void		error(void);
int			ft_usleep(int ms, int time2die, long long last_meal);

#endif
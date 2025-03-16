/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:25:01 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/03/16 00:38:07 by ayel-arr         ###   ########.fr       */
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

int		ft_atoi(const char *ptr);
int		*get_args(int argc, char **argv);
void	error(void);
void	make_threads(pthread_t	*threads, int *args, char *forks, char j);
void	*philosopher(void	*arg);

typedef struct s_philo
{
	char	*forks;
	int		*args;
	int		number;
}	t_philo;

int		check_forks(pthread_mutex_t *lock, t_philo *philo, int	forks_index[2]);

#endif
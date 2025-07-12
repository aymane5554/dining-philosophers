/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:17:02 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/12 10:39:50 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_philos(pid_t *pids, sem_t *sem)
{
	int	i;

	i = 0;
	while (pids[i] != -1)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	sem_close(sem);
	free(pids);
	exit(1);
}

void	check_fork(int i, pid_t *pids, sem_t *sem, t_arg *arg)
{
	if (pids[i] == -1)
		kill_philos(pids, sem);
	if (pids[i] == 0)
	{
		free(pids);
		arg->number = i + 1;
		philosopher(arg);
	}
}

char	*get_sem_name(int number)
{
	char	*num;
	char	*name;

	num = ft_itoa(number);
	name = ft_strjoin("_sem_ate_", num);
	free(num);
	return (name);
}

void	pick_forks(t_arg *arg)
{
	sem_wait(arg->sem);
	sem_wait(arg->end);
	printf("%lld %d has taken a fork\n",
		timenow() - start_time(), arg->number);
	sem_post(arg->end);
	sem_wait(arg->sem);
	sem_wait(arg->end);
	printf("%lld %d has taken a fork\n",
		timenow() - start_time(), arg->number);
	sem_post(arg->end);
}

void	msg(char opt, int n, sem_t *end)
{
	if (opt == 1)
	{
		sem_wait(end);
		printf("%lld %d is thinking\n", timenow() - start_time(), n);
		sem_post(end);
	}
	else if (opt == 2)
	{
		sem_wait(end);
		printf("%lld %d is eating\n", timenow() - start_time(), n);
		sem_post(end);
	}
	else if (opt == 3)
	{
		sem_wait(end);
		printf("%lld %d is sleeping\n", timenow() - start_time(), n);
		sem_post(end);
	}
}

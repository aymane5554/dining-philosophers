/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:17:02 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/30 10:31:30 by ayel-arr         ###   ########.fr       */
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

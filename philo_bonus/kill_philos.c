/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:17:02 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/29 11:28:41 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_philos(pid_t *pids, sem_t *sem, int *args)
{
	int	i;

	i = 0;
	while (pids[i] != -1)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	sem_close(sem);
	free(args);
	exit(1);
}

void	check_fork(int i, pid_t *pids, sem_t *sem, t_arg *arg)
{
	if (pids[i] == -1)
		kill_philos(pids, sem, arg->args);
	if (pids[i] == 0)
	{
		arg->number = i + 1;
		philosopher(arg);
	}
}

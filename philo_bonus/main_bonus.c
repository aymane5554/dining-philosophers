/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:37:30 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/20 11:50:25 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*timer(void	*arg)
{
	t_arg	*tt;

	tt = (t_arg *)arg;
	sem_wait(tt->sem_ate);
	while (timenow() - tt->age <= tt->args[1])
	{
		if (tt->ate[0] == 1)
		{
			sem_post(tt->sem_ate);
			return (NULL);
		}
		sem_post(tt->sem_ate);
		usleep(1000);
		sem_wait(tt->sem_ate);
	}
	sem_post(tt->sem_ate);
	sem_wait(tt->end);
	printf("%lld %d died\n", timenow() - start_time(), tt->number);
	exit(1);
	return (NULL);
}

int	timer_create_(t_arg *arg)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, timer, arg) != 0)
	{
		sem_close(arg->sem);
		sem_close(arg->sem_ate);
		sem_close(arg->end);
		exit(1);
	}
	pthread_detach(thread);
	return (0);
}

int	philosopher(t_arg *arg)
{
	int			meals;
	char		*sem_name;

	sem_name = get_sem_name(arg->number);
	arg->sem_ate = sem_open(sem_name, O_CREAT | O_EXCL, 0777, 1);
	(sem_unlink(sem_name), free(sem_name), meals = 0);
	arg->age = timenow();
	while (meals != arg->args[4])
	{
		msg(1, arg->number, arg->end);
		(sem_wait(arg->sem_ate), arg->ate[0] = 0);
		(sem_post(arg->sem_ate), timer_create_(arg), pick_forks(arg));
		(sem_wait(arg->sem_ate), arg->ate[0] = 1, sem_post(arg->sem_ate));
		msg(2, arg->number, arg->end);
		(sem_wait(arg->sem_ate), arg->age = timenow(), sem_post(arg->sem_ate));
		ft_usleep(arg->args[2], arg->args[1], arg->age, arg);
		(sem_post(arg->sem), sem_post(arg->sem));
		if (arg->args[4] != -1)
			meals++;
		msg(3, arg->number, arg->end);
		if (meals == arg->args[4])
			(sem_close(arg->sem_ate), sem_close(arg->sem), exit(0));
		ft_usleep(arg->args[3], arg->args[1], arg->age, arg);
	}
	return (sem_close(arg->sem_ate), sem_close(arg->sem), exit(0), 0);
}

void	wait_philos(int *args, pid_t *pids, sem_t *sem)
{
	int	status;
	int	i;

	i = 0;
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 1)
		{
			while (i < args[0])
			{
				kill(pids[i], SIGKILL);
				i++;
			}
			sem_close(sem);
			free(pids);
			exit(0);
		}
	}
	sem_close(sem);
	free(pids);
}

int	main(int argc, char **argv)
{
	sem_t	*sem;
	int		i;
	t_arg	arg;
	pid_t	*pids;
	sem_t	*end;

	i = 0;
	if (!get_args(argc, argv, arg.args))
		return (error(), 1);
	sem = sem_open("_sem_philo_", O_CREAT | O_EXCL, 0777, arg.args[0]);
	end = sem_open("end", O_CREAT | O_EXCL, 0777, 1);
	(sem_unlink("_sem_philo_"), sem_unlink("end"));
	arg.sem = sem;
	arg.end = end;
	pids = malloc(arg.args[0] * sizeof(pid_t));
	if (!pids)
		return (error(), 1);
	start_time();
	while (i < arg.args[0])
	{
		pids[i] = fork();
		check_fork(i, pids, sem, &arg);
		i++;
	}
	wait_philos(arg.args, pids, sem);
}

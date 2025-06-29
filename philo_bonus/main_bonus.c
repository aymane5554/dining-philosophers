/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:37:30 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/29 11:27:51 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*timer(void	*arg)
{
	t_arg	*tt;

	tt = (t_arg *)arg;
	while (timenow() - tt->age < tt->args[1])
	{
		sem_wait(tt->sem_ate);
		if (tt->ate[0] == 1)
		{
			sem_post(tt->sem_ate);
			return (NULL);
		}
		sem_post(tt->sem_ate);
		usleep(1000);
	}
	printf("%lld %d died\n", timenow() - start_time(), tt->number);
	sem_close(tt->sem_ate);
	sem_close(tt->sem);
	free(tt->args);
	exit(1);
	return (NULL);
}

int	timer_create_(t_arg *arg)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, timer, arg) == -1)
	{
		sem_close(arg->sem);
		sem_close(arg->sem_ate);
		free(arg->args);
		exit(1);
	}
	pthread_detach(thread);
	return (0);
}

int	philosopher(t_arg *arg)
{
	int			meals;

	arg->sem_ate = sem_open("sem_ate", O_RDWR | O_CREAT, 0777, 1);
	sem_unlink("sem_ate");
	meals = 0;
	arg->age = timenow();
	while (meals != arg->args[4])
	{
		printf("%lld %d is thinking\n", timenow() - start_time(), arg->number);
		sem_wait(arg->sem_ate);
		arg->ate[0] = 0;
		(sem_post(arg->sem_ate), timer_create_(arg));
		(sem_wait(arg->sem), sem_wait(arg->sem), sem_wait(arg->sem_ate));
		arg->ate[0] = 1;
		sem_post(arg->sem_ate);
		printf("%lld %d is eating\n", timenow() - start_time(), arg->number);
		arg->age = timenow();
		ft_usleep(arg->args[2], arg->args[1], arg->age);
		(sem_post(arg->sem), sem_post(arg->sem));
		printf("%lld %d is sleeping\n", timenow() - start_time(), arg->number);
		ft_usleep(arg->args[3], arg->args[1], arg->age);
		meals++;
	}
	(sem_close(arg->sem_ate), sem_close(arg->sem), free(arg->args));
	return (exit(0), 0);
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
			free(args);
			exit(0);
		}
	}
}

int	main(int argc, char **argv)
{
	int			*args;
	sem_t		*sem;
	int			i;
	t_arg		arg;
	pid_t		*pids;

	i = 0;
	args = get_args(argc, argv);
	if (!args)
		return (error(), 1);
	sem = sem_open("sem_philo", O_RDWR | O_CREAT, 0777, args[0]);
	sem_unlink("sem_philo");
	arg.args = args;
	arg.sem = sem;
	pids = malloc(args[0] * sizeof(pid_t));
	start_time();
	while (i < args[0])
	{
		pids[i] = fork();
		check_fork(i, pids, sem, &arg);
		i++;
	}
	wait_philos(args, pids, sem);
}

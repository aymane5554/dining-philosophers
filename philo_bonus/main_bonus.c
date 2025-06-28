/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:37:30 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/28 15:46:42 by ayel-arr         ###   ########.fr       */
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
	printf("%d died\n", tt->number);
	exit(0);
	return (NULL);
}

int	timer_create_(t_arg *arg)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, timer, arg);
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
		printf("%d is thinking\n", arg->number);
		sem_wait(arg->sem_ate);
		arg->ate[0] = 0;
		sem_post(arg->sem_ate);
		timer_create_(arg);
		sem_wait(arg->sem);
		sem_wait(arg->sem);
		sem_wait(arg->sem_ate);
		arg->ate[0] = 1;
		sem_post(arg->sem_ate);
		printf("%d is eating\n", arg->number);
		arg->age = timenow();
		ft_usleep(arg->args[2], arg->args[1], arg->age);
		sem_post(arg->sem);
		sem_post(arg->sem);
		printf("%d is sleeping\n", arg->number);
		ft_usleep(arg->args[3], arg->args[1], arg->age);
		meals++;
	}
	printf("%d exit\n", arg->number);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	int			*args;
	sem_t		*sem;
	int			i;
	t_arg		arg;

	i = 0;
	args = get_args(argc, argv);
	if (!args)
		return (error(), 1);
	sem = sem_open("sem_philo", O_RDWR | O_CREAT, 0777, args[0]);
	sem_unlink("sem_philo");
	arg.args = args;
	arg.sem = sem;
	while (i < args[0])
	{
		if (fork() == 0)
		{
			arg.number = i + 1;
			philosopher(&arg);
		}
		i++;
	}
	while (1)
		continue ;
}

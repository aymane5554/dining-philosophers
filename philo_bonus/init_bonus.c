/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/12 10:34:49 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_args(int argc, char **argv, int *args)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	j = 0;
	while (i < argc)
	{
		args[j] = ft_atoi(argv[i]);
		if (args[j] == -1)
			return (0);
		i++;
		j++;
	}
	if (argc == 5)
		args[4] = -1;
	return (1);
}

void	error(void)
{
	write(2, "error\n", 6);
}

long long	start_time(void)
{
	static long long	start;
	struct timeval		tv;

	if (start == 0)
	{
		gettimeofday(&tv, NULL);
		start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
	return (start);
}

long long	timenow(void)
{
	struct timeval		tv;
	long long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	ft_usleep(int ms, int time2die, long long last_meal,
		t_arg *arg)
{
	struct timeval	tv;
	long long		start;
	long long		now;
	long long		age;

	gettimeofday(&tv, NULL);
	age = last_meal;
	now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	start = now;
	while (now - start < ms)
	{
		if (now - age >= time2die)
		{
			(sem_wait(arg->end), printf("%lld %d died\n",
					timenow() - start_time(), arg->number), exit(1));
		}
		(usleep(100), gettimeofday(&tv, NULL));
		now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
	if (now - age >= time2die)
	{
		(sem_wait(arg->end), printf("%lld %d died\n",
				timenow() - start_time(), arg->number), exit(1));
	}
	return (0);
}

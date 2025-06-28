/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:24:32 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/28 14:51:14 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	*get_args(int argc, char **argv)
{
	int	*args;
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (NULL);
	args = malloc(5 * sizeof(int));
	if (args == NULL)
		return (NULL);
	i = 1;
	j = 0;
	while (i < argc)
	{
		args[j] = ft_atoi(argv[i]);
		if (args[j] == -1)
			return (free(args), NULL);
		i++;
		j++;
	}
	if (argc == 5)
		args[4] = -1;
	return (args);
}

void	error(void)
{
	write(2, "error\n", 6);
}

long long	timenow(void)
{
	struct timeval		tv;
	long long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	ft_usleep(int ms, int time2die, long long last_meal)
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
			return (1);
		usleep(100);
		gettimeofday(&tv, NULL);
		now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
	if (now - age >= time2die)
		return (1);
	return (0);
}

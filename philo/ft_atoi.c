/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:31:04 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/24 14:09:10 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pre(const char **ptr)
{
	while (**ptr == ' ' || (**ptr >= 9 && **ptr <= 13))
		*ptr = *ptr + 1;
	if (**ptr == '+')
		*ptr = *ptr + 1;
}

int	ft_atoi(const char *ptr)
{
	int			total;
	int			last;

	total = 0;
	last = 0;
	pre(&ptr);
	if (!(*ptr >= '0' && *ptr <= '9'))
		return (-1);
	while (*ptr >= '0' && *ptr <= '9')
	{
		total = (total * 10) + (*ptr - '0');
		if (total < last)
			return (-1);
		last = total;
		ptr++;
	}
	if (*ptr != '\0' || total == 0)
		return (-1);
	return (total);
}

long long	*get_args_(int argc, char **argv, long long **args)
{
	*args = get_args(argc, argv);
	if (!*args)
		return (error(), NULL);
	if (args[0][0] == 1)
		return (starving(*args), NULL);
	return (*args);
}

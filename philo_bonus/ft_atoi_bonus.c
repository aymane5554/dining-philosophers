/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:31:04 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/07/24 14:08:46 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

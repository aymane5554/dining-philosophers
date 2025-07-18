/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:03:52 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/29 15:03:53 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	int	digits(int num)
{
	int		i;

	i = 0;
	if (num < 0)
		i++;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static	int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		numlen;

	numlen = digits(n);
	if (n == 0)
		numlen = 1;
	number = malloc(numlen +1);
	if (number == NULL)
		return (NULL);
	if (n == 0)
		number[0] = '0';
	number[numlen] = '\0';
	if (n < 0)
		number[0] = '-';
	while (n != 0)
	{
		number[numlen -1] = '0' + ft_abs(n % 10);
		n /= 10;
		numlen--;
	}
	return (number);
}

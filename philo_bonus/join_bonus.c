/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:04:26 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/06/30 10:48:43 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*s;

	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	s = malloc(i + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static void	copy(char *s, char const *s1, int *i)
{
	while (s1[*i])
	{
		s[*i] = s1[*i];
		*i = *i +1 ;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup((char *)s2));
	else if (s2 == NULL)
		return (ft_strdup((char *)s1));
	s = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (s == NULL)
		return (NULL);
	copy(s, s1, &i);
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

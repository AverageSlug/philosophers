/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:31:40 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 14:39:44 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_clearall(int ret, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_detach(philo->pthread[i]);
		pthread_mutex_destroy(&philo->mutex[i]);
		i++;
	}
	if (philo->pthread)
		free(philo->pthread);
	if (philo->mutex)
		free(philo->mutex);
	return (ret);
}

int	ft_is_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	unsigned int	p;
	int				b;

	p = 0;
	b = 1;
	if (*str == '-')
	{
		if (*str++ == '-')
			b = -1;
	}
	while (*str >= 48 && *str <= 57)
		p = p * 10 + (*str++ - 48);
	return (p * b);
}

int	ft_parse(int n, char **args, t_philo *philo)
{
	int	i;

	i = 0;
	while (++i < n)
		if (!(ft_is_num(args[i])))
			return (0);
	philo->num_of_philo = ft_atoi(args[1]);
	philo->time_to_die = ft_atoi(args[2]);
	philo->time_to_eat = ft_atoi(args[3]);
	philo->time_to_sleep = ft_atoi(args[4]);
	if (n == 6)
		philo->wincon = ft_atoi(args[5]);
	else
		philo->wincon = -1;
	return (1);
}

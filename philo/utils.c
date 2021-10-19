/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:31:40 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/18 14:52:29 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_set_time(void)
{
	struct timeval	todms;

	gettimeofday(&todms, NULL);
	return (todms.tv_sec * 1000 + todms.tv_usec / 1000);
}

int	ft_clearall(t_philo *philo)
{
	int	i;

	if (philo->threads)
		free(philo->threads);
	if (philo->last)
		free(philo->last);
	if (philo->limit)
		free(philo->limit);
	if (philo->pthread)
		free(philo->pthread);
	pthread_mutex_destroy(&philo->write);
	pthread_mutex_destroy(&philo->protect);
	i = -1;
	while (++i < philo->num_of_philo)
		pthread_mutex_destroy(&philo->mutex[i]);
	if (philo->mutex)
		free(philo->mutex);
	return (1);
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

int	ft_atoi(const char *str)
{
	unsigned long long	p;
	int					boo;

	p = 0;
	boo = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str++ == '-')
			boo = -1;
	}
	while (*str >= 48 && *str <= 57)
	{
		if (p > 2147483647 && boo == 1)
			return (-1);
		else if (p > 2147483648 && boo == -1)
			return (0);
		p = p * 10 + (*str++ - 48);
	}
	return (p * boo);
}

int	ft_parse(int n, char **args, t_philo *philo)
{
	int	i;

	i = 0;
	while (++i < n)
		if (!(ft_is_num(args[i])))
			return (0);
	philo->num_of_philo = ft_atoi(args[1]);
	if (philo->num_of_philo <= 0 || philo->num_of_philo >= 201)
		return (0);
	philo->time_to_die = ft_atoi(args[2]);
	if (philo->time_to_die <= 59)
		return (0);
	philo->time_to_eat = ft_atoi(args[3]);
	if (philo->time_to_eat <= 59)
		return (0);
	philo->time_to_sleep = ft_atoi(args[4]);
	if (philo->time_to_sleep <= 59)
		return (0);
	if (n == 6)
		philo->wincon = ft_atoi(args[5]);
	else
		philo->wincon = -1;
	if (n == 6 && philo->wincon <= 0)
		return (0);
	return (1);
}

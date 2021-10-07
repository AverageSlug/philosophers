/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:34:35 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/07 18:36:25 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philos(t_philo *philo)
{
	int				i;
	struct timeval	t;
	pthread_t		pthread;

	i = 0;
	philo->threads[0].win = 0;
	gettimeofday(&t, NULL);
	philo->threads[0].initial_time = t.tv_sec * 1000 + t.tv_usec / 1000;
	while (i < philo->num_of_philo)
	{
		philo->index = i;
		if (pthread_create(&pthread, NULL, ft_philoop, (void *)philo))
			return (0);
		pthread_detach(pthread);
		i += 2;
		usleep(20);
	}
	i = 1;
	while (i < philo->num_of_philo)
	{
		philo->index = i;
		if (pthread_create(&pthread, NULL, ft_philoop, (void *)philo))
			return (0);
		pthread_detach(pthread);
		i += 2;
		usleep(20);
	}
	if (pthread_create(&pthread, NULL, ft_checkloop, (void *)philo))
		return (0);
	pthread_detach(pthread);
	usleep(60);
	pthread_mutex_lock(&philo->dead);
	pthread_mutex_unlock(&philo->dead);
	usleep(1000);
	return (1);
}

int	ft_pthread(t_philo *philo)
{
	int	i;

	philo->mutex = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	if (!philo->mutex)
		return (0);
	philo->threads = malloc(sizeof(t_threads) * philo->num_of_philo);
	if (!philo->threads)
		return (0);
	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->threads[i].status = 5;
		pthread_mutex_init(&philo->mutex[i++], NULL);
	}
	pthread_mutex_init(&philo->dead, NULL);
	if (!(ft_philos(philo)))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
		return (1);
	if (!(ft_parse(argc, argv, &philo)))
		return (1);
	if (!(ft_pthread(&philo)))
		return (ft_clearall(&philo));
	ft_clearall(&philo);
	return (0);
}

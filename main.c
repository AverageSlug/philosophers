/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:34:35 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/18 14:37:37 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_create(t_philo *philo, int i)
{
	while (i < philo->num_of_philo)
	{
		philo->threads[i].philo = philo;
		philo->threads[i].index = i;
		if (pthread_create(&philo->pthread[i], NULL, ft_philoop,
				(void *)&philo->threads[i]))
			return (1);
		i += 2;
		usleep(20);
	}
	return (0);
}

int	ft_create_all(t_philo *philo)
{
	if (ft_philo_create(philo, 0))
		return (0);
	ft_usleep(10);
	if (ft_philo_create(philo, 1))
		return (0);
	ft_usleep(10);
	if (pthread_create(&philo->pthread[philo->num_of_philo], NULL,
			ft_checkloop, (void *)philo))
		return (0);
	return (1);
}

int	ft_philos(t_philo *philo)
{
	int	i;

	philo->win = 0;
	philo->end = 0;
	philo->init = ft_set_time();
	philo->pthread = malloc(sizeof(pthread_t) * (philo->num_of_philo + 1));
	if (!philo->pthread)
		return (0);
	philo->last = malloc(sizeof(int) * philo->num_of_philo);
	if (!philo->last)
		return (0);
	philo->limit = malloc(sizeof(int) * philo->num_of_philo);
	if (!philo->limit)
		return (0);
	i = 0;
	while (i < philo->num_of_philo)
		philo->last[i++] = ft_set_time();
	if (!ft_create_all(philo))
		return (0);
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
		if (pthread_mutex_init(&philo->mutex[i++], NULL))
			return (0);
	if (pthread_mutex_init(&philo->write, NULL))
		return (0);
	if (pthread_mutex_init(&philo->protect, NULL))
		return (0);
	if (!(ft_philos(philo)))
		return (0);
	i = 0;
	while (i <= philo->num_of_philo)
		pthread_join(philo->pthread[i++], NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (!(ft_parse(argc, argv, &philo)))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (!(ft_pthread(&philo)))
	{
		printf("Error: Program failed\n");
		return (ft_clearall(&philo));
	}
	ft_clearall(&philo);
	return (0);
}

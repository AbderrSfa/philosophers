/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:22:09 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/17 15:21:01 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *philo)
{
	printf("Philosopher %d is sleeping.\n", philo->philo_number);
	usleep(TIME_TO_SLEEP * 1000);
}

void	eating(t_philo *philo)
{
	printf("Philosopher %d is eating.\n", philo->philo_number);
	usleep(TIME_TO_EAT * 1000);
}

void	thinking(t_philo *philo)
{
	printf("Philosopher %d is thinking.\n", philo->philo_number);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

t_philo	*create_philos()
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * NUM_OF_PHILOS);
	if (philo == NULL)
		return (NULL);
	while (i < NUM_OF_PHILOS)
	{
		philo[i].philo_number = i + 1;
		i++;
	}
	return (philo);
}

pthread_t	*create_threads(t_philo *philo)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * NUM_OF_PHILOS);
	if (threads == NULL)
		return (NULL);
	while (i < NUM_OF_PHILOS)
	{
		if (pthread_create(&threads[i], NULL, &routine, &philo[i]))
			return (NULL);
		usleep(1500 * 1000);
		i++;
	}
	return (threads);
}

int		main()
{
	t_philo		*philo;
	pthread_t	*threads;
	int		i;

	philo = create_philos();
	threads = create_threads(philo);
	i = 0;
	while (i < NUM_OF_PHILOS)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
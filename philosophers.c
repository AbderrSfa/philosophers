/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:22:09 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/17 16:22:27 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *philo)
{
	printf("Philosopher %d is sleeping.\n", philo->philo_id);
	usleep(TIME_TO_SLEEP * 1000);
}

void	eating(t_philo *philo)
{
	philo->meal_number++;
	printf("Philosopher %d is eating. Meal number: %d\n", philo->philo_id, philo->meal_number);
	usleep(TIME_TO_EAT * 1000);
}

void	thinking(t_philo *philo)
{
	printf("Philosopher %d is thinking.\n", philo->philo_id);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (philo->meal_number == NUM_OF_MEALS && NUM_OF_MEALS != 0)
			return (NULL);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	initialize_philo(t_philo *philo, int i)
{
	philo->philo_id = i + 1;
	philo->meal_number = 0;
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
		initialize_philo(&philo[i], i);
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

int		main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	*threads;
	t_runtime	runtime;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments.");
		return (0);
	}
	parsing(argc, argv, &runtime);
	philo = create_philos();
	threads = create_threads(philo);
	i = 0;
	while (i < NUM_OF_PHILOS)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}

/* 		i = 0;
		while (i < NUM_OF_PHILOS)
		{
			printf("Philo number: %d\n", philo[i].philo_id);
			printf("Philo meal number: %d\n", philo[i].meal_number);
			i++;
		} */
	return (0);
}
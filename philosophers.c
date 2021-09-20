/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:22:09 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/20 14:19:47 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize_philo(t_philo *philo, t_runtime *runtime, int i)
{
	philo->philo_id = i + 1;
	philo->meal_number = 0;
	philo->runtime = runtime;
}

t_philo	*create_philos(t_runtime *runtime)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * runtime->philo_number);
	if (philo == NULL)
		return (NULL);
	while (i < runtime->philo_number)
	{
		initialize_philo(&philo[i], runtime, i);
		i++;
	}
	return (philo);
}

pthread_t	*create_threads(t_philo *philo)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * philo->runtime->philo_number);
	if (threads == NULL)
		return (NULL);
	while (i < philo->runtime->philo_number)
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
	t_runtime	*runtime;
	int		i;

	if (argc < 5 || argc > 6)
		ft_put_error("Invalid number of arguments.");
	runtime = parsing(argc, argv);
	philo = create_philos(runtime);
	threads = create_threads(philo);
	i = 0;
	while (i < philo->runtime->philo_number)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}

/* 		i = 0;
		while (i < philo->runtime->philo_number)
		{
			printf("Philo number: %d\n", philo[i].philo_id);
			printf("Philo meal number: %d\n", philo[i].meal_number);
			i++;
		} */
	return (0);
}
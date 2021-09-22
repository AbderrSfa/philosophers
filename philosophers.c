/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:22:09 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/22 13:58:42 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize_philo(t_philo *philo, t_runtime *runtime, int i)
{
	philo->philo_id = i + 1;
	philo->meal_number = 0;
	philo->runtime = runtime;
	philo->time_of_last_meal = 0;
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
		if (pthread_create(&threads[i], NULL, routine, &philo[i]))
			return (NULL);
		usleep(1000 * 1000);
		i++;
	}
	return (threads);
}

unsigned int	get_time()
{
	struct timeval	time_start;

	gettimeofday(&time_start, NULL);
	return ((time_start.tv_sec * 1000) + (time_start.tv_usec / 1000));
}

void	init_mutexes(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->runtime->philo_number)
	{
		pthread_mutex_init(&philo->runtime->forks[i], NULL);
		i++;
	}
}

void	destroy_mutexes(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->runtime->philo_number)
	{
		pthread_mutex_destroy(philo->runtime->forks);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	*threads;
	t_runtime	*runtime;
	int		i;

	if (argc < 5 || argc > 6)
		return (ft_put_error("Invalid number of arguments."));
	if (!(runtime = parsing(argc, argv)))
		return (1);
	runtime->start_time = get_time();
	philo = create_philos(runtime);
	threads = create_threads(philo);
	init_mutexes(philo);
	i = 0;
	while (i < philo->runtime->philo_number)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	destroy_mutexes(philo);
	return (0);
}
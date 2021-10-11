/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:50:47 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/11 14:46:32 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_init_philo(t_runtime *runtime, t_philo *philo, int i)
{
	philo[i].philo_id = i + 1;
	philo[i].left_hand = i;
	philo[i].right_hand = (i + 1) % runtime->number_of_philos;
	philo[i].sim_info = runtime;
	philo[i].meals_eaten = 0;
	philo[i].next_meal_time = 0;
	philo[i].prev_meal_time = 0;
}

void	ft_destroy_mutexes(t_runtime *runtime)
{
	int		i;

	i = 0;
	while (i < runtime->number_of_philos)
	{
		pthread_mutex_destroy(&runtime->forks[i]);
		i++;
	}
	pthread_mutex_destroy(runtime->end);
}

int	ft_init_mutexes(t_runtime *runtime)
{
	int		i;

	i = 0;
	while (i < runtime->number_of_philos)
	{
		if (pthread_mutex_init(&runtime->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(runtime->end, NULL))
		return (1);
	return (0);
}

t_philo	*ft_create_philos(t_runtime *runtime)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * runtime->number_of_philos);
	if (philo == NULL)
		return (NULL);
	while (i < runtime->number_of_philos)
	{
		ft_init_philo(runtime, philo, i);
		i++;
	}
	return (philo);
}
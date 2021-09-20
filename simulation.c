/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:45:39 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/20 13:00:43 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *philo)
{
	printf("Philosopher %d is sleeping.\n", philo->philo_id);
	usleep(philo->runtime->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	philo->meal_number++;
	printf("Philosopher %d is eating. Meal number: %d\n", philo->philo_id, philo->meal_number);
	usleep(philo->runtime->time_to_eat * 1000);
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
		if (philo->meal_number == philo->runtime->times_eaten && philo->runtime->times_eaten != 0)
			return (NULL);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

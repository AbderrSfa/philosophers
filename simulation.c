/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:45:39 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/21 15:20:11 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *philo)
{
	printf("%d Philosopher %d is sleeping.\n", get_time() - philo->runtime->start_time, philo->philo_id);
	usleep(philo->runtime->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	philo->meal_number++;
	printf("%d Philosopher %d is eating. Meal number: %d\n", get_time() - philo->runtime->start_time, philo->philo_id, philo->meal_number);
	usleep(philo->runtime->time_to_eat * 1000);
	philo->time_of_last_meal = get_time();
}

void	thinking(t_philo *philo)
{
	printf("%d Philosopher %d is thinking.\n", get_time() - philo->runtime->start_time, philo->philo_id);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->time_of_last_meal = get_time();
	while (1)
	{
		if ((get_time() - philo->time_of_last_meal) > philo->runtime->time_to_die)
		{
			printf("%d Philosopher %d died.\n", get_time() - philo->runtime->start_time, philo->philo_id);
			return (NULL);
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->meal_number == philo->runtime->times_eaten && philo->runtime->times_eaten != 0)
			return (NULL);
	}
	return (NULL);
}

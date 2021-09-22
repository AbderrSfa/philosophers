/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:45:39 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/22 14:53:02 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(int dead, char *status, t_philo *philo)
{
	if (dead == 0)
		printf("%u %d is %s.\n", get_time() - philo->runtime->start_time, philo->philo_id, status);	
	else
		printf("\033[0;31m%u %d died.\n\033[0m", get_time() - philo->runtime->start_time, philo->philo_id);

}

void	sleeping(t_philo *philo)
{
	print_status(0, "sleeping", philo);
	usleep(philo->runtime->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	philo->meal_number++;
	print_status(0, "eating", philo);
	usleep(philo->runtime->time_to_eat * 1000);
	philo->time_of_last_meal = get_time();
	if (pthread_mutex_unlock(&philo->runtime->forks[philo->left_hand]))
		exit(EXIT_FAILURE);
	if (pthread_mutex_unlock(&philo->runtime->forks[philo->right_hand]))
		exit(EXIT_FAILURE);

}

void	thinking(t_philo *philo)
{
	print_status(0, "thinking", philo);
}

void	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->runtime->forks[philo->left_hand]))
		exit(EXIT_FAILURE);
	printf("%u %d has taken a fork.\n", get_time() - philo->runtime->start_time, philo->philo_id);	
	if (pthread_mutex_lock(&philo->runtime->forks[philo->right_hand]))
		exit(EXIT_FAILURE);
	printf("%u %d has taken a fork.\n", get_time() - philo->runtime->start_time, philo->philo_id);	
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
			print_status(1, NULL, philo);
			return (NULL);
		}
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->meal_number == philo->runtime->times_eaten && philo->runtime->times_eaten != 0)
			return (NULL);
	}
	return (NULL);
}

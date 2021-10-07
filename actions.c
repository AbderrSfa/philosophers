/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:25:13 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/07 14:25:46 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *philo)
{
	print_status(0, "thinking", philo);
}

void	sleeping(t_philo *philo)
{
	print_status(0, "sleeping", philo);
	usleep(philo->sim_info->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	philo->meals_eaten++;
	print_status(0, "eating", philo);
	philo->time_of_last_meal = get_time();
	usleep(philo->sim_info->time_to_eat * 1000);
	if (pthread_mutex_unlock(&philo->sim_info->forks[philo->left_hand]))
		exit(EXIT_FAILURE);
	if (pthread_mutex_unlock(&philo->sim_info->forks[philo->right_hand]))
		exit(EXIT_FAILURE);
}

void	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->sim_info->forks[philo->left_hand]))
		exit(EXIT_FAILURE);
	printf("%u %d has taken a fork. last_meal %u\n", get_time() - philo->sim_info->start_time, philo->philo_id, (get_time() - philo->time_of_last_meal));	
	if (pthread_mutex_lock(&philo->sim_info->forks[philo->right_hand]))
		exit(EXIT_FAILURE);
	printf("%u %d has taken a fork. last_meal %u\n", get_time() - philo->sim_info->start_time, philo->philo_id, (get_time() - philo->time_of_last_meal));	
}
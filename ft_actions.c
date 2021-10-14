/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:48:58 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/14 11:36:04 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print_status(char *status, t_philo *philo)
{
	pthread_mutex_lock(philo->sim_info->print);
	printf("%u %d is %s. previous meal: %u\n",
		(ft_get_time() - philo->sim_info->start_time), philo->philo_id, status,
		(ft_get_time() - philo->prev_meal_time));
	pthread_mutex_unlock(philo->sim_info->print);
}

void	ft_sleeping(t_philo *philo)
{
	ft_print_status("sleeping", philo);
	usleep(philo->sim_info->time_to_sleep * 1000);
}

void	ft_eating(t_philo *philo)
{
	ft_print_status("eating", philo);
	init_times(philo);
	philo->meals_eaten++;
	usleep(philo->sim_info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->sim_info->forks[philo->left_hand]);
	pthread_mutex_unlock(&philo->sim_info->forks[philo->right_hand]);
}

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_info->forks[philo->left_hand]);
	printf("%u %d has taken a fork.\n",
		ft_get_time() - philo->sim_info->start_time, philo->philo_id);
	pthread_mutex_lock(&philo->sim_info->forks[philo->right_hand]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:48:58 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/12 11:55:19 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print_status(int death, char *status, t_philo *philo)
{
	pthread_mutex_lock(philo->sim_info->print);
	if (death == 1)
	{
		printf("%u %d died. previous meal: %u\n",
			ft_get_time() - philo->sim_info->start_time, philo->philo_id,
			(ft_get_time() - philo->prev_meal_time));
	}
	else
	{
		printf("%u %d is %s. previous meal: %u\n",
			(ft_get_time() - philo->sim_info->start_time), philo->philo_id, status,
			(ft_get_time() - philo->prev_meal_time));
		pthread_mutex_unlock(philo->sim_info->print);
	}
}

void	ft_sleeping(t_philo *philo)
{
	ft_print_status(0, "sleeping", philo);
	usleep(philo->sim_info->time_to_sleep * 1000);
}

void	ft_eating(t_philo *philo)
{
	ft_print_status(0, "eating", philo);
	philo->prev_meal_time = ft_get_time();
	philo->next_meal_time = ft_get_time()
		+ (unsigned int)philo->sim_info->time_to_die;
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

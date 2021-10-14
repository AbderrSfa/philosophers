/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:48:34 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/14 11:35:57 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_get_time(void)
{
	struct timeval	time_start;

	gettimeofday(&time_start, NULL);
	return ((time_start.tv_sec * 1000) + (time_start.tv_usec / 1000));
}

void	init_times(t_philo *philo)
{
	philo->prev_meal_time = ft_get_time();
	philo->next_meal_time = ft_get_time()
		+ (unsigned int)philo->sim_info->time_to_die;
}

static void	*ft_dead_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (philo->next_meal_time < ft_get_time())
		{
			pthread_mutex_lock(philo->sim_info->print);
			printf("%u %d died. previous meal: %u\n",
				ft_get_time() - philo->sim_info->start_time, philo->philo_id,
				(ft_get_time() - philo->prev_meal_time));
			pthread_mutex_unlock(philo->sim_info->end);
		}
	}
	return (NULL);
}

void	*ft_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death;

	philo = arg;
	init_times(philo);
	pthread_create(&death, NULL, ft_dead_philo, philo);
	pthread_detach(death);
	while (1)
	{
		ft_take_forks(philo);
		ft_eating(philo);
		if (philo->meals_eaten >= philo->sim_info->meals_to_eat
			&& philo->sim_info->meals_to_eat != -1)
		{
			printf("%u %d done eating.\n",
				ft_get_time() - philo->sim_info->start_time, philo->philo_id);
			break ;
		}
		ft_sleeping(philo);
		ft_print_status("thinking", philo);
	}
	return (NULL);
}

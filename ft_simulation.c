/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:48:34 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/12 11:52:07 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*ft_dead_philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (philo->next_meal_time < ft_get_time())
		{
			ft_print_status(1, NULL, philo);
			printf("\033[0;31m****\n\033[0m");
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
	philo->prev_meal_time = ft_get_time();
	philo->next_meal_time = ft_get_time()
		+ (unsigned int)philo->sim_info->time_to_die;
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
		ft_print_status(0, "thinking", philo);
	}
	return (NULL);
}

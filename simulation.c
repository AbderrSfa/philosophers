/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:45:39 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/27 10:49:48 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	get_time()
{
	struct timeval	time_start;

	gettimeofday(&time_start, NULL);
	return ((time_start.tv_sec * 1000) + (time_start.tv_usec / 1000));
}

void	print_status(int dead, char *status, t_philo *philo)
{
	pthread_mutex_lock(philo->sim_info->print);
	if (dead == 1)
		printf("%u \033[0;31m%d died. last_meal: %u\n\033[0m", get_time() - philo->sim_info->start_time, philo->philo_id, (get_time() - philo->time_of_last_meal));
	else
		printf("%u %d is %s. last_meal: %u\n", get_time() - philo->sim_info->start_time, philo->philo_id, status, (get_time() - philo->time_of_last_meal));
	pthread_mutex_unlock(philo->sim_info->print);
}

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

void	*dead_philo(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = arg;
	i = 0;
	while (1)
	{
		if (philo->sim_info->philo_dead)
			exit(EXIT_SUCCESS);
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death;

	philo = arg;
	philo->time_of_last_meal = get_time();
	pthread_create(&death, NULL, dead_philo, philo);
	while (1)
	{
		take_forks(philo);
		if ((get_time() - philo->time_of_last_meal) > philo->sim_info->time_to_die)
		{
			print_status(1, NULL, philo);
			philo->sim_info->philo_dead = 1;
			return (NULL);
		}
		eating(philo);
		if (philo->meals_eaten == philo->sim_info->meals_to_eat && philo->sim_info->meals_to_eat != 0)
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
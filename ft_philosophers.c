/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:46:26 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/15 14:39:52 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_set_the_table(t_runtime runtime, t_philo *philo)
{
	int		i;

	i = 0;
	pthread_mutex_lock(runtime.end);
	while (i < runtime.number_of_philos)
	{
		if (pthread_create(&runtime.threads[i], NULL, ft_routine, &philo[i]))
			return (1);
		pthread_detach(runtime.threads[i]);
		usleep(50);
		i++;
	}
	pthread_mutex_lock(runtime.end);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_runtime	runtime;

	if (argc < 5 || argc > 6)
		return (ft_put_error(&runtime, "Invalid number of arguments."));
	if (ft_parsing(argc, argv, &runtime))
		return (1);
	philo = ft_create_philos(&runtime);
	if (ft_set_the_table(runtime, philo))
		ft_put_error(&runtime, "Allocation error.");
	ft_destroy_mutexes(philo, &runtime);
	return (0);
}

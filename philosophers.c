/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:22:09 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/28 10:06:36 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_runtime *runtime)
{
	int		i;

	i = 0;
	while (i < runtime->number_of_philos)
	{
		if (pthread_mutex_init(&runtime->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(runtime->print, NULL))
		return (1);
	return (0);
}

void	init_philo(t_runtime *runtime, t_philo *philo, int i)
{
	philo[i].philo_id = i + 1;
	philo[i].left_hand = i;
	philo[i].right_hand = (i + 1) % runtime->number_of_philos;
	philo[i].meals_eaten = 0;
	philo[i].sim_info = runtime;
	philo[i].time_of_last_meal = 0;
}

t_philo	*create_philos(t_runtime *runtime)
{
	t_philo	*philo;
	int		i;

	i = 0;
	runtime->threads = malloc(sizeof(pthread_t) * runtime->number_of_philos);
	runtime->forks = malloc(sizeof(pthread_mutex_t) * runtime->number_of_philos);	
	runtime->print = malloc(sizeof(pthread_mutex_t));
	philo = malloc(sizeof(t_philo) * runtime->number_of_philos);
	if (philo == NULL)
		return (NULL);
	while (i < runtime->number_of_philos)
	{
		init_philo(runtime, philo, i);
		i++;
	}
	return (philo);
}

void	destroy_mutexes(t_runtime *runtime)
{
	int		i;

	i = 0;
	while (i < runtime->number_of_philos)
	{
		pthread_mutex_destroy(&runtime->forks[i]);
		i++;
	}
	pthread_mutex_destroy(runtime->print);
}

int		main(int argc, char **argv)
{
	t_philo		*philo;
	t_runtime	runtime;
	pthread_mutex_t kill;
	int			i;

	if (argc < 5 || argc > 6)
		return (ft_put_error("Invalid number of arguments."));
	if (parsing(argc, argv, &runtime))
		return (1);
	runtime.start_time = get_time();
	philo = create_philos(&runtime);
	if (init_mutexes(&runtime))
		return (ft_put_error("Allocation error."));
	i = 0;
	pthread_mutex_init(&kill, NULL);
	pthread_mutex_lock(&kill);
	while (i < runtime.number_of_philos)
	{
		if (pthread_create(&runtime.threads[i], NULL, routine, &philo[i]))
			return (ft_put_error("Allocation error."));
		pthread_detach(runtime.threads[i]);
		usleep(1000);
		i++;
	}
	i = 0;
	pthread_mutex_lock(&kill);	
/* 	while (i < runtime.number_of_philos)
	{
		if (pthread_join(runtime.threads[i], NULL))
			return (ft_put_error("Allocation error."));
		i++;
	} */
	destroy_mutexes(&runtime);
/* 	i = 0;
	printf("\033[1;34mSimulation Info:\033[0m\n");
	printf("number_philos: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\nnumber_of_meals: %d\n", runtime.number_of_philos, runtime.time_to_die, runtime.time_to_eat, runtime.time_to_sleep, runtime.number_of_meals);
	while (i < philo->sim_info->number_of_philos)
	{
		printf("\n\033[1;32mPhilo Info:\033[0m\n");
		printf("philo_ID: %d\nleft_hand: %d\nright_hand: %d\nmeal_number: %d\ntime_of_last_meal: %d\n", philo[i].philo_id, philo[i].left_hand, philo[i].right_hand, philo[i].meal_number, philo[i].time_of_last_meal);
		i++;
	} */


	return (0);
}
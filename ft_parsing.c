/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:48:00 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/17 11:13:37 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_put_error(t_runtime *runtime, char *error)
{
	printf("ERROR:\033[0;33m %s\n\033[0m", error);
	return (1);
	if (runtime->threads)
		free(runtime->threads);
	if (runtime->forks)
		free(runtime->forks);
	if (runtime->end)
		free(runtime->end);
	if (runtime->print)
		free(runtime->print);
	if (runtime->done)
		free(runtime->done);
}

static int	ft_validate_args(t_runtime *runtime)
{
	if (runtime->number_of_philos < 1)
		return (ft_put_error(runtime,
				"There has to be at least 1 philosopher."));
	else if (runtime->number_of_philos > 200)
		return (ft_put_error(runtime,
				"Only enough chairs for 200 philosophers."));
	else if (runtime->time_to_die < 60)
		return (ft_put_error(runtime, "Time to die cannot be under 60 ms."));
	else if (runtime->time_to_eat < 60)
		return (ft_put_error(runtime, "Time to eat cannot be under 60 ms."));
	else if (runtime->time_to_sleep < 60)
		return (ft_put_error(runtime, "Time to sleep cannot be under 60 ms."));
	return (0);
}

static int	ft_is_arg_valid(char **argv)
{
	int		i;
	int		j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{		
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_parsing(int argc, char **argv, t_runtime *runtime)
{
	if (ft_is_arg_valid(argv))
		return (ft_put_error(runtime, "Invalid argument."));
	runtime->number_of_philos = ft_atoi(argv[1]);
	runtime->time_to_die = ft_atoi(argv[2]);
	runtime->time_to_eat = ft_atoi(argv[3]);
	runtime->time_to_sleep = ft_atoi(argv[4]);
	runtime->meals_to_eat = 0;
	if (argc == 6)
		runtime->meals_to_eat = ft_atoi(argv[5]);
	runtime->philo_dead = 0;
	runtime->finished_philos = 0;
	if (ft_validate_args(runtime))
		return (1);
	runtime->start_time = ft_get_time();
	runtime->threads = malloc(sizeof(pthread_t) * runtime->number_of_philos);
	runtime->forks = malloc(sizeof(pthread_mutex_t)
			* runtime->number_of_philos);
	runtime->end = malloc(sizeof(pthread_mutex_t));
	runtime->print = malloc(sizeof(pthread_mutex_t));
	runtime->done = malloc(sizeof(pthread_mutex_t));
	if (ft_init_mutexes(runtime))
		return (ft_put_error(runtime, "Allocation error."));
	return (0);
}

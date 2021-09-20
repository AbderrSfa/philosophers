/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:48:41 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/20 14:23:17 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_arg_valid(char **argv)
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
				ft_put_error("Invalid argument.");
			j++;
		}
		i++;
	}
	return (0);
}

void		init_runtime(t_runtime *runtime)
{
	runtime->philo_number = 0;
	runtime->time_to_die = 0;
	runtime->time_to_eat = 0;
	runtime->time_to_sleep = 0;
	runtime->times_eaten = 0;
}

void		validate_args(t_runtime *runtime)
{
	if (runtime->philo_number < 1)
		ft_put_error("There has to be at least 1 philosopher.");
	else if (runtime->philo_number > 200)
		ft_put_error("Not enough chairs for 200 philosophers.");
	else if (runtime->time_to_die < 60)
		ft_put_error("Time to die cannot be under 60 ms.");
	else if (runtime->time_to_eat < 60)
		ft_put_error("Time to eat cannot be under 60 ms.");
	else if (runtime->time_to_sleep < 60)
		ft_put_error("Time to sleep cannot be under 60 ms.");
}

t_runtime	*parsing(int argc, char **argv)
{
	t_runtime	*runtime;

	runtime = malloc(sizeof(t_runtime));
	init_runtime(runtime);
	if (is_arg_valid(argv))
		exit(1);
	runtime->philo_number = ft_atoi(argv[1]);
	runtime->time_to_die = ft_atoi(argv[2]);
	runtime->time_to_eat = ft_atoi(argv[3]);
	runtime->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		runtime->times_eaten = ft_atoi(argv[5]);
	validate_args(runtime);
	return (runtime);
}
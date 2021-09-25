/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:48:41 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/25 11:16:29 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_args(t_runtime *runtime)
{
	if (runtime->number_of_philos < 1)
		return (ft_put_error("There has to be at least 1 philosopher."));
	else if (runtime->number_of_philos > 200)
		return (ft_put_error("Only enough chairs for 200 philosophers."));
	else if (runtime->time_to_die < 60)
		return (ft_put_error("Time to die cannot be under 60 ms."));
	else if (runtime->time_to_eat < 60)
		return (ft_put_error("Time to eat cannot be under 60 ms."));
	else if (runtime->time_to_sleep < 60)
		return (ft_put_error("Time to sleep cannot be under 60 ms."));
	return (0);
}

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
				return (ft_put_error("Invalid argument."));
			j++;
		}
		i++;
	}
	return (0);
}

int	parsing(int argc, char **argv, t_runtime *runtime)
{
	if (is_arg_valid(argv))
		return (1);
	runtime->number_of_meals = -1;
	runtime->number_of_philos = ft_atoi(argv[1]);
	runtime->time_to_die = ft_atoi(argv[2]);
	runtime->time_to_eat = ft_atoi(argv[3]);
	runtime->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		runtime->number_of_meals = ft_atoi(argv[5]);
	if (validate_args(runtime))
		return (1);
	return (0);
}
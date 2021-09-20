/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:48:41 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/20 12:44:20 by asfaihi          ###   ########.fr       */
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
			{
				printf("Invalid argument.\n");
				return (1);
			}
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
	return (runtime);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:22:11 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/17 15:13:35 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define NUM_OF_PHILOS 5
#define TIME_TO_DIE 800
#define TIME_TO_EAT 200
#define TIME_TO_SLEEP 200
#define NUM_OF_MEALS 0

int				forks[NUM_OF_PHILOS];
long			start_of_program;

typedef struct	s_philo
{
	int			philo_num;
	int			meal_num;
	long		time_since_last_meal;
}				t_philo;

void	eating(int philo_num, t_philo *philo)
{
	struct timeval	timeStart;

	gettimeofday(&timeStart, NULL);
	philo->time_since_last_meal = timeStart.tv_sec;
	printf("%ld %d is eating meal number %d.\n", (timeStart.tv_sec - start_of_program), philo_num, philo->meal_num + 1);
	usleep(TIME_TO_EAT * 1000);
	forks[philo_num] = 0;
	forks[(philo_num % NUM_OF_PHILOS) + 1] = 0;
	philo->meal_num++;
}

void	sleeping(int philo_num)
{
	struct timeval	timeStart;

	gettimeofday(&timeStart, NULL);
	printf("%ld %d is sleeping.\n", (timeStart.tv_sec - start_of_program), philo_num);
	usleep(TIME_TO_SLEEP * 1000);
}

void	*routine(void *arg)
{
	struct timeval	timeStart;
	t_philo	*philo;
	int		i;

	philo = arg;
	i = philo->philo_num;
	while (1)
	{
		if (philo->meal_num == NUM_OF_MEALS && NUM_OF_MEALS != 0)
			return (NULL);
		gettimeofday(&timeStart, NULL);
		if (((timeStart.tv_sec - philo->time_since_last_meal) * 1000) > TIME_TO_DIE)
		{
			printf("Philosopher %d died After %ld!", philo->philo_num, (timeStart.tv_sec - philo->time_since_last_meal) * 1000);
			exit(1);
		}
		sleeping(i);
		gettimeofday(&timeStart, NULL);
		printf("%ld %d is thinking.\n", (timeStart.tv_sec - start_of_program), philo->philo_num);
		while (1)
		{
			gettimeofday(&timeStart, NULL);
			if (((timeStart.tv_sec - philo->time_since_last_meal) * 1000) > TIME_TO_DIE)
			{
				printf("Philosopher %d died After %ld!", philo->philo_num, (timeStart.tv_sec - philo->time_since_last_meal) * 1000);
				exit(1);
			}
			if (forks[i] == 0 || forks[(i % NUM_OF_PHILOS) + 1] == 0)
			{
				if (forks[i] == 0)
				{
					forks[i] = i;
					gettimeofday(&timeStart, NULL);
					printf("%ld %d has taken a fork.\n", (timeStart.tv_sec - start_of_program), i);
				}
				if (forks[(i % NUM_OF_PHILOS) + 1] == 0)
				{
					forks[(i % NUM_OF_PHILOS) + 1] = i;
					gettimeofday(&timeStart, NULL);
					printf("%ld %d has taken a fork.\n", (timeStart.tv_sec - start_of_program), i);
				}
				if (forks[i] == i && forks[(i % NUM_OF_PHILOS) + 1] == i)
				{
					eating(i, philo);
					break;
				}
			}
		}
	}
}

void	initialize_philo(t_philo *philo, int i)
{
	struct timeval	timeStart;

	philo->philo_num = i + 1;
	philo->meal_num = 0;
	gettimeofday(&timeStart, NULL);
	philo->time_since_last_meal = timeStart.tv_sec;
}

int		main(int argc, char **argv)
{
	struct timeval	timeStart;
	pthread_t	th[NUM_OF_PHILOS];
	t_philo		philo[NUM_OF_PHILOS];
	int			i;

	gettimeofday(&timeStart, NULL);
	start_of_program = timeStart.tv_sec;
	i = 0;
	while (i < NUM_OF_PHILOS)
		forks[i++] = 0;
	i = 0;
	while (i < NUM_OF_PHILOS)
	{
		initialize_philo(&philo[i], i);
		i++;
	}
	i = 0;
	while (i < NUM_OF_PHILOS)
	{
		if (pthread_create(&th[i], NULL, &routine, &philo[i]))
			return (1);
		usleep(1000 * 1000);
		i++;
	}
	i = 0;
	while (i < NUM_OF_PHILOS)
	{
		if (pthread_join(th[i], NULL))
			return (1);
		i++;
	}
	i = 0;
	return (0);
}
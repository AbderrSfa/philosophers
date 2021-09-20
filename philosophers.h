/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:22:07 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/20 12:56:02 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define NUM_OF_PHILOS 3
# define TIME_TO_EAT 2000
# define TIME_TO_SLEEP 2000
# define NUM_OF_MEALS 3

typedef	struct	s_runtime
{
	int			philo_number;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_eaten;
}				t_runtime;


typedef struct	s_philo
{
	int				philo_id;
	int				meal_number;
	pthread_mutex_t	mutex;
	t_runtime		*runtime;
}				t_philo;

/* Libft functions */
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);

/* Parsing inputs */
void		init_runtime(t_runtime *runtime);
t_runtime	*parsing(int argc, char **argv);

/* Simultion */
t_philo		*create_philos(t_runtime *runtime);
void		initialize_philo(t_philo *philo, t_runtime *runtime, int i);
pthread_t	*create_threads(t_philo *philo);
void		*routine(void *arg);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

#endif
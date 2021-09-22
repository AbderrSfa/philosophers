/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:22:07 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/22 13:48:14 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define RESET	"\033[0m"
# define RED	"\033[0;31m"
# define GREEN	"\033[1;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"

typedef	struct		s_runtime
{
	pthread_mutex_t	*forks;
	int				philo_number;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				times_eaten;
	unsigned int	start_time;
}					t_runtime;


typedef struct		s_philo
{
	t_runtime		*runtime;
	int				philo_id;
	int				meal_number;
	unsigned int	time_of_last_meal;
}					t_philo;

/* Libft functions */
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);

/* Parsing inputs */
t_runtime		*parsing(int argc, char **argv);
int				is_arg_valid(char **argv);
void			init_runtime(t_runtime *runtime);
int				validate_args(t_runtime *runtime);
int				ft_put_error(char *error);

/* Simultion */
t_philo			*create_philos(t_runtime *runtime);
void			initialize_philo(t_philo *philo, t_runtime *runtime, int i);
pthread_t		*create_threads(t_philo *philo);
unsigned int	get_time();
void			*routine(void *arg);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);

#endif
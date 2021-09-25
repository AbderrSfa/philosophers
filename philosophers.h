/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:22:07 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/25 11:19:27 by asfaihi          ###   ########.fr       */
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
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	int				number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				number_of_meals;
	unsigned int	start_time;
}					t_runtime;


typedef struct		s_philo
{
	t_runtime		*sim_info;
	int				philo_id;
	int				left_hand;
	int				right_hand;
	int				meal_number;
	unsigned int	time_of_last_meal;
}					t_philo;

/* Parsing inputs */
int					parsing(int argc, char **argv, t_runtime *runtime);
int					is_arg_valid(char **argv);
int					validate_args(t_runtime *runtime);

/* Initializing philos & mutexes */
t_philo				*create_philos(t_runtime *runtime);
void				init_philo(t_runtime *runtime, t_philo *philo, int i);
int					init_mutexes(t_runtime *runtime);

/* Simultion */
void				*routine(void *arg);
void				take_forks(t_philo *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				print_status(int dead, char *status, t_philo *philo);
unsigned int		get_time();

/* Libft functions */
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
int					ft_put_error(char *error);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:46:23 by asfaihi           #+#    #+#             */
/*   Updated: 2021/10/15 14:45:31 by asfaihi          ###   ########.fr       */
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

typedef struct s_runtime
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*end;
	pthread_mutex_t	*print;
	pthread_mutex_t	*done;
	int				number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				meals_to_eat;
	unsigned int	start_time;
	int				philo_dead;
	int				finished_philos;
}					t_runtime;

typedef struct s_philo
{
	t_runtime		*sim_info;
	pthread_mutex_t	*eat;
	int				philo_id;
	int				left_hand;
	int				right_hand;
	int				meals_eaten;
	unsigned int	next_meal_time;
	unsigned int	prev_meal_time;
}					t_philo;

/* Parsing inputs */
int					ft_parsing(int argc, char **argv, t_runtime *runtime);
int					ft_put_error(t_runtime *runtime, char *error);

/* Init / destroy philosophers */
t_philo				*ft_create_philos(t_runtime *runtime);
int					ft_init_mutexes(t_runtime *runtime);
void				ft_destroy_mutexes(t_philo *philo, t_runtime *runtime);

/* Simultion */
void				*ft_routine(void *arg);
void				ft_take_forks(t_philo *philo);
void				ft_eating(t_philo *philo);
void				ft_sleeping(t_philo *philo);
unsigned int		ft_get_time(void);
void				init_times(t_philo *philo);
void				ft_print_status(char *status, t_philo *philo);

/* Libft functions */
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
#endif

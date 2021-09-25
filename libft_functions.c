/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:58:47 by asfaihi           #+#    #+#             */
/*   Updated: 2021/09/25 11:19:20 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_put_error(char *error)
{
	printf("ERROR:\033[0;33m %s\n\033[0m", error);
	return (1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	i;
	long	bn;

	bn = n;
	i = 1;
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		if (n < 0)
		{
			bn = -bn;
			ft_putchar_fd('-', fd);
		}
		while ((bn / (i * 10)) != 0)
			i = (i * 10);
		while (i != 0)
		{
			ft_putchar_fd((bn / i) + 48, fd);
			bn = (bn % i);
			i = (i / 10);
		}
	}
}

int	ft_isdigit(int c)
{
	if ((c > 47 && c < 58))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	a;
	int		b;
	int		c;

	a = 0;
	b = 0;
	c = 1;
	while (((*str <= 13) && (*str >= 9)) || (*str == 32))
		str++;
	while ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			c = -1;
		b++;
		str++;
	}
	if (b > 1)
		return (0);
	while ((*str <= '9') && (*str >= '0'))
	{
		a = (*str - 48) + a * 10;
		str++;
	}
	return (a * c);
}

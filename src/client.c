/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoissar <lcoissar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:47:18 by lcoissar          #+#    #+#             */
/*   Updated: 2022/12/15 08:47:18 by lcoissar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>//
#include <signal.h>
#include <unistd.h>

static void	ft_putstr(char *str)
{
	while (*str)
		write(1, &*str++, 1);
}

// à corriger
int	ft_atoi(const char *str)
{
	int						i;
	int						sign;
	long long unsigned int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > LLONG_MAX)
		{
			if (sign > 0)
				return (-1);
			else
				return (0);
		}
	}
	return (sign * result);
}

void	sig_sender(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac != 3)
	{
		ft_putstr("error\n");
		return (1);
	}
	pid = ft_atoi(av[1]);
	//secure pid ?
	while (av[2][i])
		sig_sender(pid, av[2][i++]);
	sig_sender(pid, '\n');
	return (0);
}

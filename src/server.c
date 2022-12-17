/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoissar <lcoissar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:47:15 by lcoissar          #+#    #+#             */
/*   Updated: 2022/12/16 11:01:58 by lcoissar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

static void	ft_putstr(char *str)
{
	while (*str)
		write(1, &*str++, 1);
}

static void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			n = -n;
			write(1, &"-", 1);
		}
		if (n > 9)
		{
			ft_putnbr((n / 10));
			c = n % 10 + '0';
			write(1, &c, 1);
		}
		else
		{
			c = n + '0';
			write(1, &c, 1);
		}
	}
}

static void	sig_handler(int signal)
{
	static int	bit = 0;
	static int	i = 0;

	if (signal == SIGUSR1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &i, 1);
		bit = 0;
		i = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_putstr("pid :");
	ft_putnbr(pid);
	ft_putstr("\n");
	signal(SIGUSR1, &sig_handler);
	signal(SIGUSR2, &sig_handler);
	while (1)
		pause();
	return (0);
}

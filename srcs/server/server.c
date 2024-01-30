/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:22:31 by gcros             #+#    #+#             */
/*   Updated: 2024/01/30 22:38:28 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "server.h"

void	ft_putnbr(int n);

int main(int ac, char **av)
{
	(void)av;
	if (ac != 1)
		return (-1);
	ft_server_init();
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
}

void	ft_putnbr(int n)
{
	int	c;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n / 10 > 0)
	{
		ft_putnbr(n / 10);
	}
	c = n % 10 + '0';
	write(1, &c, 1);
}

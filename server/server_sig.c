/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:22:32 by gcros             #+#    #+#             */
/*   Updated: 2024/01/26 01:28:11 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700

#include <signal.h>
#include "server.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

t_message	*g_client_message;

void    get_pid(int sig, siginfo_t *info, void *context);
void    ft_signal_handler(int sig, siginfo_t *info, void *context);

void	ft_server_init()
{
	static t_sigaction	sa = {0};
	
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_signal_handler;

	if (sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0)
		exit(-2);
	write (1, "init\n", 5);
}

int	ft_send_sig(int sig, int pid)
{
	return (kill(pid, sig));
}

int	resolve_message(int sig)
{
	int	ret;

	ret = 0;
	ret = ft_receive(sig);
	if (ret == 1)
		write(1, g_client_message->message, g_client_message->message_cursor);
	if (ret == 1 || ret == -1)
	{
		free(g_client_message->message);
		free(g_client_message);
		g_client_message = NULL;
	}
	return (ret);
}

void    ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	
	
	if (g_client_message == NULL)
		g_client_message = ft_init_message(info->si_pid);
	if (g_client_message == NULL)
		exit (-1);
	if (g_client_message->from == info->si_pid)
	{
		if (resolve_message(sig) == -1)
		{
			ft_send_sig(SIGUSR2, info->si_pid);
			exit (-1);
		}
		if (ft_send_sig(SIGUSR1, info->si_pid))
		{
			free(g_client_message->message);
			free(g_client_message);
			g_client_message = NULL;
		}
	}
	else
		ft_send_sig(SIGUSR2, info->si_pid);
}

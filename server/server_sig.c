/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:22:32 by gcros             #+#    #+#             */
/*   Updated: 2024/01/30 17:40:48 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700

#include <signal.h>
#include "server.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

int	resolve_message(int sig, pid_t pid)
{
	static t_message	*message;
	int	ret;

	if (pid == 0 && message != NULL)
	{
		free (message->message);
		free (message);
		message = NULL;
		return (-1);
	}
	if (message == NULL)
		message = ft_init_message(pid);
	if (message == NULL)
		return (-1);
	ret = ft_receive(sig, pid, message);
	if (ret == -1 || ret == 1)
	{
		free (message->message);
		free (message);
		message = NULL;
	}
	return (ret);
}

void    ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	if (resolve_message(sig, info->si_pid) == -1)
	{
		ft_send_sig(SIGUSR2, info->si_pid);
		exit (-1);
	}
	if (ft_send_sig(SIGUSR1, info->si_pid) == -1)
	{
		resolve_message(0, 0);
		exit (-1);
	}
}

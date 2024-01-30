/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:22:32 by gcros             #+#    #+#             */
/*   Updated: 2024/01/30 23:20:43 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define _XOPEN_SOURCE 700
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"

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
}

int	ft_send_sig(int sig, int pid)
{
	return (kill(pid, sig));
}

int	resolve_message(int sig, pid_t pid)
{
	static t_message	*message;
	int	ret;

	if (pid == 0)
	{
		if (message != NULL)
			free (message->message);
		if (message != NULL)
			free (message);
		message = NULL;
		return (-1);
	}
	if (message == NULL)
		message = ft_init_message(pid);
	if (message == NULL)
		return (-1);
	ret = ft_receive(sig, message);
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
	(void) context;
	if (resolve_message(sig, info->si_pid) == -1)
	{
		ft_send_sig(SIGUSR2, info->si_pid);
		exit (-1);
	}
	if (ft_send_sig(SIGUSR1, info->si_pid) == -1)
	{
		resolve_message(0, 0);
	}
}

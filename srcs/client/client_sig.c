/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:07:55 by gcros             #+#    #+#             */
/*   Updated: 2024/01/30 22:36:11 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700

#include <signal.h>
#include "client.h"
#include <unistd.h>
#include <stdlib.h>

int g_server_feedback = 0;

void    get_pid(int sig, siginfo_t *info, void *context);
void    ft_signal_handler(int sig, siginfo_t *info, void *context);

void	ft_client_init()
{
	static t_sigaction	sa;
	
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_signal_handler;

	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
		exit(-2);
}

int	get_feedback()
{
	int f;
	
	f = 0;
	while (g_server_feedback == 0)
		;
	f = g_server_feedback;
	g_server_feedback = 0;
	return (f);
}

int	ft_send_bit(int bit, int pid)
{
	static int	sig_set[] = {SIGUSR2, SIGUSR1};
	
	//printf("send %d to %d\n", bit, pid);
	return (kill(pid, sig_set[bit]));
}

void    ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	g_server_feedback = sig;
}
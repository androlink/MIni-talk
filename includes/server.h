/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:22:29 by gcros             #+#    #+#             */
/*   Updated: 2024/01/30 23:22:49 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define _XOPEN_SOURCE 700

# include <signal.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct sigaction t_sigaction;
typedef unsigned char t_byte;

typedef enum e_srv_flag
{
	SRV_YES,
	SRV_PANIC,
	SRV_STOP
}	t_srv_flag;

typedef struct s_message
{
	int		from;
	t_byte	*message;
	size_t	message_cursor;
	size_t	message_len;
}	t_message;

void		ft_server_init();
int			ft_receive(int sig, t_message *message);
int			resolve_message(int sig, pid_t pid);
int			ft_send_sig(int sig, int pid);
t_message	*ft_init_message(int from);
void		ft_signal_handler(int sig, siginfo_t *info, void *context);

#endif
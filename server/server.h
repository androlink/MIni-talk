/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:22:29 by gcros             #+#    #+#             */
/*   Updated: 2024/01/25 18:22:11 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <signal.h>

# define BUFFER_SIZE 100

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
	t_byte	byte;
	size_t	message_cursor;
	size_t	message_len;
	int		byte_cursor;
	size_t	timeout;
}	t_message;

void		ft_server_init();
int			ft_receive(int sig);
int			ft_send_sig(int sig, int pid);
t_message	*ft_init_message(int from);

#endif
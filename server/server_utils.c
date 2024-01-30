/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:27:06 by gcros             #+#    #+#             */
/*   Updated: 2024/01/25 18:19:09 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "server.h"

void	ft_fill_byte(int bit);
int		ft_fill_string();
int		ft_expend(void);

extern t_message *g_client_message;

t_message	*ft_init_message(int from)
{
	t_message	*message;

	message = malloc(sizeof(t_message));
	if (message == NULL)
		return (NULL);
	message->message = malloc(sizeof(t_byte)*10);
	if (message->message == NULL)
		return (free(message), NULL);
	message->byte = 0;
	message->byte_cursor = 0;
	message->from = from;
	message->message_len = 10;
	message->message_cursor = 0;
	return (message);
}


int	ft_receive(int sig)
{
	ft_fill_byte(sig == SIGUSR1);
	if (g_client_message->byte_cursor == 8)
		return (ft_fill_string());
	return (0);
}

void	ft_fill_byte(int bit)
{
	if (g_client_message->byte_cursor < 8)
	{
		g_client_message->byte <<= 1;
		g_client_message->byte += bit;
		g_client_message->byte_cursor++;
	}
}

int	ft_fill_string(void)
{
	if (g_client_message->byte == 0)
		return (1);
	if (g_client_message->message_cursor == g_client_message->message_len)
		if (ft_expend() == -1)
			return (-1);
	g_client_message->message[g_client_message->message_cursor] = g_client_message->byte;
	g_client_message->message_cursor++;
	g_client_message->byte_cursor = 0;
	return (0);
}

int	ft_expend(void)
{
	t_byte	*nbuf;
	size_t	i;

	nbuf = malloc(g_client_message->message_len + 10);
	if (nbuf == NULL)
		return (-1);
	i = 0;
	while (i < g_client_message->message_len)
	{
		nbuf[i] = g_client_message->message[i];
		i++;
	}
	nbuf[i] = '\0';
	free(g_client_message->message);
	g_client_message->message = nbuf;
	g_client_message->message_len += 10;
	return (1);
}

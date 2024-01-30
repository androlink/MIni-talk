/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:27:06 by gcros             #+#    #+#             */
/*   Updated: 2024/01/30 23:23:12 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "server.h"
#include <stdlib.h>

int	ft_fill_byte(int bit, t_byte *byte);
int	ft_expend(t_message *message);

t_message	*ft_init_message(int from)
{
	t_message	*message;

	message = malloc(sizeof(t_message));
	if (message == NULL)
		return (NULL);
	message->message = malloc(sizeof(t_byte)*BUFFER_SIZE);
	if (message->message == NULL)
		return (free(message), NULL);
	message->message[0] = '\0';
	message->from = from;
	message->message_len = 10;
	message->message_cursor = 0;
	return (message);
}


int	ft_receive(int sig, t_message *message)
{
	int	ret;
	
	if (ft_fill_byte(sig == SIGUSR1, &message->message[message->message_cursor]))
	{
		if (message->message[message->message_cursor] == '\0')
		{
			ret = write(1, message->message, message->message_cursor);
			if (ret == -1)
				return (-1);
			return (1);
		}
		message->message_cursor++;
		if (message->message_cursor == message->message_len)
		if (ft_expend(message) == -1)
			return (-1);
		message->message[message->message_cursor] = '\0';
	}
	return (0);
}

int	ft_fill_byte(int bit, t_byte *byte)
{
	static int	cursor;

	if (cursor < 8)
	{
		*byte <<= 1;
		*byte += bit;
		cursor++;
	}
	if (cursor == 8)
	{
		cursor = 0;
		return (1);
	}
	return (0);
}

int	ft_expend(t_message *message)
{
	t_byte	*nbuf;
	size_t	i;

	nbuf = malloc(message->message_len + BUFFER_SIZE);
	if (nbuf == NULL)
		return (-1);
	i = 0;
	while (i < message->message_len)
	{
		nbuf[i] = message->message[i];
		i++;
	}
	nbuf[i] = '\0';
	free(message->message);
	message->message = nbuf;
	message->message_len += BUFFER_SIZE;
	return (1);
}

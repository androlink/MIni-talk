/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:29:17 by gcros             #+#    #+#             */
/*   Updated: 2024/01/31 00:11:58 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

typedef unsigned char		t_byte;
typedef struct sigaction	t_sigaction;

void	ft_client_init(void);
int		ft_send_bit(int bit, int pid);
int		get_feedback(void);

#endif
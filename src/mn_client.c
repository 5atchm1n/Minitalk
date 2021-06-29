/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mn_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:48:03 by sshakya           #+#    #+#             */
/*   Updated: 2021/06/29 16:14:35 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	mn_error(int error)
{
	if (error == 1)
		ft_putstr_fd("Usage : ./client [PID] [message]\n", 1);
	if (error == 2)
		ft_putstr_fd("Signal error\n", 1);
	if (error == 3)
		ft_putstr_fd("Invalid PID\n", 1);
	exit (0);
}

void	mn_ascii(int pid, unsigned char c)
{
	uint8_t	bit;

	bit = 1 << 6;
	while (bit)
	{
		if (c & bit)
		{
			if (kill(pid, SIGUSR1) != 0)
				mn_error(3);
		}
		else
			if (kill(pid, SIGUSR2) != 0)
				mn_error(3);
		bit >>= 1;
		usleep(TIME);
	}
}

void	mn_receipt(int sig, siginfo_t *var, void *param)
{
	(void)sig;
	(void)param;
	(void)var;
	ft_putstr_fd("Message delivered\n", 1);
}

void	mn_message(char *id, char *message)
{
	int	pid;
	int	i;

	i = 0;
	pid = ft_atoi(id);
	while (message[i] != '\0')
	{
		mn_ascii(pid, message[i]);
		i++;
	}
	mn_ascii(pid, message[i++]);
}

int	main(int argc, char **argv)
{
	struct sigaction	msg;

	msg.sa_flags = SA_SIGINFO;
	msg.sa_sigaction = mn_receipt;
	if (sigaction(SIGUSR2, &msg, 0) != 0)
		mn_error(2);
	if (argc != 3)
		mn_error(1);
	mn_message(argv[1], argv[2]);
	return (0);
}

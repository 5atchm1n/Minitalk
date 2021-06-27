/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mn_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:48:03 by sshakya           #+#    #+#             */
/*   Updated: 2021/06/27 20:05:34 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	mn_ascii(int pid, unsigned char c)
{
	uint8_t	byte;

	byte = 1 << 6;
	while (byte)
	{
		if (c & i)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit (0);
		}
		else
			if (kill(pid, SIGUSR2) == -1)
				exit (0);
		i >>= 1;
		usleep(600);
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

	msg.sa_flags = SA_SIGINFO | SA_NODEFER;
	msg.sa_sigaction = mn_receipt;
	if (sigaction(SIGUSR2, &msg, 0) != 0)
		exit (0);
	if (argc != 3)
		return (0);
	mn_message(argv[1], argv[2]);
	return (0);
}

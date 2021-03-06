/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mn_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshakya <sshakya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:48:11 by sshakya           #+#    #+#             */
/*   Updated: 2021/06/29 15:40:35 by sshakya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_mtalk	g_message = {{0}, (1 << 6), 0, 0};

static int	mn_error(int error)
{
	if (error == 1)
		ft_putstr_fd("Error\n", 1);
	if (error == 2)
		ft_putstr_fd("Signal error\n", 1);
	exit (0);
}

void	mn_on(int sig, siginfo_t *var, void *param)
{
	(void)sig;
	(void)var;
	(void)param;
	if (g_message.bit == 0)
	{
		g_message.bit = (1 << 6);
		g_message.index += 1;
	}
	g_message.msg[g_message.index] += g_message.bit;
	g_message.bit >>= 1;
	if (g_message.index == BUFFSIZE - 2 && g_message.bit == 0)
		g_message.flag |= LIMIT;
}

void	mn_off(int sig, siginfo_t *var, void *param)
{
	(void)sig;
	(void)param;
	if (g_message.bit == 0)
	{
		g_message.bit = (1 << 6);
		g_message.index += 1;
	}
	g_message.bit >>= 1;
	if (g_message.index == BUFFSIZE - 2 && !g_message.bit)
		g_message.flag |= LIMIT;
	else if (g_message.msg[g_message.index] == '\0' && !g_message.bit)
	{
		g_message.flag |= DONE;
		kill(var->si_pid, SIGUSR2);
	}
}

int	mn_handler(void)
{
	while (1)
	{
		pause();
		if (g_message.flag & DONE || g_message.flag & LIMIT)
		{
			ft_putstr_fd(g_message.msg, 1);
			ft_bzero(g_message.msg, BUFFSIZE);
			g_message.index = 0;
			g_message.bit = (1 << 6);
			if (g_message.flag & DONE)
				write(1, "\n", 1);
			g_message.flag = 0;
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	on;
	struct sigaction	off;

	(void)argv;
	if (argc != 1)
		return (mn_error(1));
	on.sa_sigaction = mn_on;
	off.sa_sigaction = mn_off;
	on.sa_flags = SA_SIGINFO;
	off.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &on, 0) != 0)
		return (mn_error(2));
	if (sigaction(SIGUSR2, &off, 0) != 0)
		return (mn_error(2));
	pid = getpid();
	ft_putstr_fd("Server is ready !\nPID : ", 1);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	ft_bzero(g_message.msg, BUFFSIZE);
	mn_handler();
}

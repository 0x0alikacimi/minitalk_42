/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:24:04 by abkacimi          #+#    #+#             */
/*   Updated: 2024/03/06 20:05:15 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	hndl_sig(int sig, siginfo_t *info, void *none)
{
	static char	byte;
	static int	i;
	int			bit;
	static int	sender_pid;

	bit = 0;
	if (sender_pid == 0)
		sender_pid = info->si_pid;
	if (sender_pid != info->si_pid)
	{
		sender_pid = info->si_pid;
		byte = 0;
		i = 0;
	}
	if (sig == SIGUSR1)
		bit = 1;
	byte = byte << 1 | bit;
	i++;
	if (i == 8)
	{
		write(1, &byte, 1);
		byte = 0;
		i = 0;
	}
	(void)none;
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_flags = SA_SIGINFO;// let us use sigaction if we put 0 => default behaveure dyalha
	sa.sa_sigaction = &hndl_sig;
	pid = getpid();
	ft_putnbr(pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

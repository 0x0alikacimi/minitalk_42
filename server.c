/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:24:04 by abkacimi          #+#    #+#             */
/*   Updated: 2024/03/10 20:20:35 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	hndl_sig(int sig, siginfo_t *info, void *none)
{
	static char	c;
	static int	i;
	int			bit;
	static int	sender_pid;

	bit = 0;
	if (sender_pid == 0)
		sender_pid = info->si_pid;
	if (sender_pid != info->si_pid)
	{
		sender_pid = info->si_pid;
		c = 0;
		i = 0;
	}
	if (sig == SIGUSR1)
		bit = 1;
	c = c << 1 | bit;
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		c = 0;
		i = 0;
	}
	(void)none;
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &hndl_sig;
	pid = getpid();
	ft_putnbr(pid);
	ft_putchar('\n');
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

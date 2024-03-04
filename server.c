/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:24:04 by abkacimi          #+#    #+#             */
/*   Updated: 2024/03/04 21:36:03 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <unistd.h>
#include <stdio.h>
#include <signal.h>
void ft_putchar(char c)
{
	write(1, &c, 1);
}
void	ft_putnbr(int n)
{
	long nb;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putchar((nb % 10) + 48);
		ft_putnbr(nb * 10);
	}
	else 
		ft_putchar(nb + 48);
}

void hndl_sig(int sig, siginfo_t *info, void *none)
{
	static char byte;
	static int i;
	int bit = 0;
	static int sender_pid;

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

int main(void)
{
    int pid;
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &hndl_sig;

    pid = getpid();
    printf("%d\n", pid);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
    while (1)
    {
        pause();
    }
    return (0);
}
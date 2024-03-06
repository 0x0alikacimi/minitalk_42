/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:37:53 by abkacimi          #+#    #+#             */
/*   Updated: 2024/03/06 18:54:04 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_byte(int pid, char c)
{
	int	b;

	b = 7;
	while (b >= 0)
	{
		if ((c >> b) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		b--;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (3 == ac)
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0)
			ft_perror("bad pid\n");
		while (av[2][i])
		{
			ft_send_byte(pid, av[2][i]);
			i++;
		}
	}
	else
		ft_perror("no valid args\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:37:53 by abkacimi          #+#    #+#             */
/*   Updated: 2024/03/09 00:01:46 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_byte(int pid, char c)
{
	int	b;

	b = 7;
	while (b >= 0)
	{
		if ((c >> b) & 1)
		{
			if (kill(pid, SIGUSR1) < 0)
			{
				ft_perror("kill error!\n");
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
			{
				ft_perror("kill error!\n");
			}
		}
		usleep(500);
		b--;
	}
}

int checkdigits(char *s)
{
	if (*s == '\0')
		return (0);
	while ((*s <= '9') && (*s >= '0'))
		s++;
	return (*s == '\0');
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		i;

	if (3 == ac)
	{
		pid = ft_atoi(av[1]);
		if ((checkdigits(av[1]) == 0) || (pid <= 0))
			ft_perror("Bad pid\n");
		i = 0;
		while (av[2][i])
		{
			ft_send_byte(pid, av[2][i]);
			i++;
		}
	}
	else
		ft_perror("Invalid args\n");
	return (0);
}

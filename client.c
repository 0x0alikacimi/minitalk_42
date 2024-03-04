/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:37:53 by abkacimi          #+#    #+#             */
/*   Updated: 2024/03/04 21:37:54 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void ft_send_byte(int pid, char c)
{
	int b;

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

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int res;
	sign = 1;
	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (sign * res);
}


int main (int ac, char **av)
{
	int pid;
	int i;
	i = 0;
	if (3 == ac)
	{
		pid = ft_atoi(av[1]);
		while(av[2][i])
		{
			ft_send_byte(pid, av[2][i]);
			i++;
		}
	}
	else
	{
		printf("errrrrror\n");
		return(1);
	}
	return (0);
}
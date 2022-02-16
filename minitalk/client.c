/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macar <macar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:31:31 by macar             #+#    #+#             */
/*   Updated: 2022/02/08 20:15:51 by macar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	kill_checker(pid_t pid, int sign)
{
	if (kill(pid, sign) == -1)
	{
		ft_printf("errooorrrrr :/");
		exit(1);
	}
}

void	send_bits(unsigned char c, pid_t pid)
{
	int	count;

	count = 7;
	while (count >= 0)
	{
		if ((c >> count) & 1)
			kill_checker(pid, SIGUSR1);
		else
			kill_checker(pid, SIGUSR2);
		count--;
		usleep(200);
	}
}

void	sended(int signo)
{
	(void)signo;
	ft_printf("mesaj clienttan gitti");
}

int	main(int argc, char **argv)
{
	pid_t	serverpid;
	char	*data;
	int		i;

	if (argc < 3)
		return (1);
	i = 2;
	serverpid = ft_atoi(argv[1]);
	signal(SIGUSR1, sended);
	while (i < argc)
	{
		data = argv[i];
		while (*data)
			send_bits(*data++, serverpid);
		i++;
	}
	send_bits('\0', serverpid);
	return (0);
}

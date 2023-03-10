/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pory <pory@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:30:17 by ory               #+#    #+#             */
/*   Updated: 2023/02/15 12:57:05 by pory             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_invalid_arg(void)
{
	printf("Error: Invalid argument\n");
	return (1);
}

int	check_arg(int argc, char **argv)
{
	int					i;
	unsigned long int	nb;

	if (!(argc == 5 || argc == 6))
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (digit_check(argv[i]))
			return (1);
		nb = ft_atoi(argv[i]);
		if (argc == 6 && ft_atoi(argv[5]) == 0)
			return (print_invalid_arg());
		if (i == 1 && (nb <= 0 || nb > 200))
			return (print_invalid_arg());
		if (i != 1 && (nb < 0 || nb > 2147483647))
			return (print_invalid_arg());
		i++;
	}
	return (0);
}

int	digit_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
		{
			printf("Error: Invalid argument\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	long long int		num;
	int					neg;

	i = 0;
	num = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * neg);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

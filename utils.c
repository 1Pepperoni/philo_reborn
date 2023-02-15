/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pory <pory@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:34:02 by ory               #+#    #+#             */
/*   Updated: 2023/02/15 11:10:26 by pory             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	death_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->print);
	if (philo->var->dead == 1)
	{
		pthread_mutex_unlock(&philo->var->print);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->var->print);
	return (0);
}

// void	philo_sleep2(unsigned long time_to_sleep)
// {
// 	unsigned long long end;

// 	//printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
// 	end = time_ms() + time_to_sleep;
// 	while (time_ms() < end)
// 	{
// 		usleep(1);
// 	}
// }

int	ft_usleep(useconds_t usec, t_philo *philo)
{
	useconds_t	start;
	useconds_t	after;

	start = time_ms();
	after = start;
	while (after - start < usec)
	{
		if (death_stop(philo))
			break ;
		usleep(50);
		after = time_ms();
	}
	return (0);
}

// void	philo_sleep(unsigned long time_to_sleep, t_philo *philo)
// {
// 	unsigned long end;

// 	//printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
// 	end = time_ms() + time_to_sleep;
// 	while (time_ms() < end)
// 	{
// 		if (death_stop(philo))
// 			break ;
// 		usleep(1);
// 	}
// }

void	print(char *str, unsigned long time, int id, t_philo *philo)
{
	pthread_mutex_lock(&philo->var->print);
	if (philo->var->dead != 1)
	{
		printf("%lu %d %s", time, id, str);
		pthread_mutex_unlock(&philo->var->print);
	}
}

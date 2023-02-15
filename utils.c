/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pory <pory@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:34:02 by ory               #+#    #+#             */
/*   Updated: 2023/02/12 19:55:50 by pory             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int	time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	death_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->var->print);
	//pthread_mutex_lock(&philo->m_last_meal);
	//pthread_mutex_lock(&philo->var->m_dead2);
	if (philo->var->dead == 1)
	{
		//pthread_mutex_unlock(&philo->var->m_dead2);
		pthread_mutex_unlock(&philo->var->print);
		//printf("philo[%d] ooooooooooooooooooooo\n", philo->id);
		//pthread_mutex_unlock(&philo->var->m_dead2);
		//pthread_mutex_unlock(&philo->m_last_meal);
		return(1);
	}
	else
	{
		pthread_mutex_unlock(&philo->var->print);
		//pthread_mutex_unlock(&philo->m_last_meal);
		//printf("aaaaaaaaaaaaaaaaaaaaaa\n");
		//pthread_mutex_unlock(&philo->var->m_dead2);
	}
	return(0);
}

void	philo_sleep2(unsigned long time_to_sleep)
{
	unsigned long long end;

	//printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
	end = time_ms() + time_to_sleep;
	while (time_ms() < end)
	{
		usleep(1);
	}
}

void	philo_sleep(unsigned long time_to_sleep, t_philo *philo)
{
	unsigned long end;

	//printf("wwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
	end = time_ms() + time_to_sleep;
	while (time_ms() < end)
	{
		if (death_stop(philo))
			break ;
		usleep(1);
	}
}
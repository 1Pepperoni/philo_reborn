/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pory <pory@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:35:16 by pory              #+#    #+#             */
/*   Updated: 2023/02/15 11:37:41 by pory             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_diff_die(t_philo *philo)
{
	unsigned long	time;
	int				i;

	i = 0;
	if ((int)time_ms() - (int)philo->last_meal >= \
		(int)philo->var->time_to_die)
	{
		philo->var->dead = 1;
		time = time_ms() - philo->var->time_zero;
		printf("%lu %d is dead\n", time, philo->id + 1);
		pthread_mutex_unlock(&philo->var->print);
		pthread_mutex_unlock(&philo->var->m_dead);
		usleep(3000000);
		return (1);
	}
	return (0);
}

int	check_everyone_ate(t_philo *philo)
{
	if (philo->var->everyone_ate == \
		philo->var->number_of_philosophers)
	{
		usleep(1000000);
		pthread_mutex_unlock(&philo->var->m_dead);
		return (1);
	}
	return (0);
}

void	*philo_checker(void *ph)
{
	t_philo			*philo;
	int				i;

	i = 0;
	philo = (t_philo *)ph;
	while (1)
	{
		pthread_mutex_lock(&philo[i].m_last_meal);
		pthread_mutex_lock(&philo[i].var->print);
		pthread_mutex_lock(&philo[i].var->m_everyone_ate);
		if (check_diff_die(&philo[i]))
			return (0);
		else if (check_everyone_ate(&philo[i]))
			return (0);
		pthread_mutex_unlock(&philo[i].m_last_meal);
		pthread_mutex_unlock(&philo[i].var->print);
		pthread_mutex_unlock(&philo[i].var->m_everyone_ate);
		if (i == philo[i].var->number_of_philosophers - 1)
			i = -1;
		i++;
	}
}

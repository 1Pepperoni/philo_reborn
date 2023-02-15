/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   happymeal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pory <pory@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:57:41 by pory              #+#    #+#             */
/*   Updated: 2023/02/15 13:00:44 by pory             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	last_meal(t_philo	*ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if ((philo->id) % 2 == 1)
		ft_usleep(100, philo);
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = time_ms();
	pthread_mutex_unlock(&philo->m_last_meal);
}

void	min_eats(t_philo *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	pthread_mutex_lock(&philo->m_last_meal);
	if ((int)philo->nb_meal == philo->var->must_eat)
	{
		pthread_mutex_lock(&philo->var->m_everyone_ate);
		philo->var->everyone_ate++;
		pthread_mutex_unlock(&philo->var->m_everyone_ate);
	}
	pthread_mutex_unlock(&philo->m_last_meal);
	print("is sleeping\n", time_ms() - philo->var->time_zero, \
		philo->id + 1, philo);
	ft_usleep(philo->var->time_to_sleep, philo);
	print("is thinking\n", time_ms() - philo->var->time_zero, \
		philo->id + 1, philo);
}

void	eats(t_philo *ph, int next_id, int id)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	pthread_mutex_lock(&philo->var->fork[id]);
	print("has taken a fork\n", time_ms() - philo->var->time_zero, \
		philo->id + 1, philo);
	pthread_mutex_lock(&philo->var->fork[next_id]);
	print("has taken a fork\n", time_ms() - philo->var->time_zero, \
		philo->id + 1, philo);
	print("is eating\n", time_ms() - philo->var->time_zero, \
		philo->id + 1, philo);
	pthread_mutex_lock(&philo->m_last_meal);
	philo->nb_meal++;
	philo->last_meal = time_ms();
	pthread_mutex_unlock(&philo->m_last_meal);
	ft_usleep(philo->var->time_to_eat, philo);
	pthread_mutex_unlock(&philo->var->fork[id]);
	pthread_mutex_unlock(&philo->var->fork[next_id]);
}

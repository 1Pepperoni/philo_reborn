/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pory <pory@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:43:36 by ory               #+#    #+#             */
/*   Updated: 2023/02/15 11:22:44 by pory             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_everyone_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal);
	pthread_mutex_lock(&philo->var->print);
	pthread_mutex_lock(&philo->var->m_everyone_ate);
	if (philo->var->everyone_ate == philo->var->number_of_philosophers)
		return (1);
	else
	{
		pthread_mutex_unlock(&philo->m_last_meal);
		pthread_mutex_unlock(&philo->var->print);
		pthread_mutex_unlock(&philo->var->m_everyone_ate);
	}
	return (0);
}

// int	last_meal_time_calc(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->m_last_meal);
// 	pthread_mutex_lock(&philo->var->print);
// 	if ((int)time_ms() - (int)philo->last_meal >= (int)philo->var->time_to_die)
// 	{
// 		return (1);
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(&philo->m_last_meal);
// 		pthread_mutex_unlock(&philo->var->print);
// 	}
// 	return (0);
// }

int	check_diff_die(t_philo *philo)
{
	unsigned long	time;
	int				i;

	i = 0;
	if ((int)time_ms() - (int)philo[i].last_meal >= \
		(int)philo[i].var->time_to_die)
	{
		philo[i].var->dead = 1;
		time = time_ms() - philo[i].var->time_zero;
		printf("%lu %d is dead\n", time, philo[i].id + 1);
		pthread_mutex_unlock(&philo[i].var->print);
		pthread_mutex_unlock(&philo[i].var->m_dead);
		usleep(3000000);
		return (1);
	}
	return (0);
}

void	*philo_checker(void *ph)
{
	t_philo			*philo;
	
	philo = (t_philo *)ph;
	while (1)
	{
		pthread_mutex_lock(&philo[i].m_last_meal);
		pthread_mutex_lock(&philo[i].var->print);
		pthread_mutex_lock(&philo[i].var->m_everyone_ate);
		check_diff_die(philo);
		else if (philo[i].var->everyone_ate == \
			philo[i].var->number_of_philosophers)
		{
			usleep(1000000);
			pthread_mutex_unlock(&philo[i].var->m_dead);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].m_last_meal);
		pthread_mutex_unlock(&philo[i].var->print);
		pthread_mutex_unlock(&philo[i].var->m_everyone_ate);
		if (i == philo[i].var->number_of_philosophers - 1)
			i = -1;
		i++;
	}
}

void	*philo_routine(void *ph)
{
	int		id;
	int		next_id;
	t_philo	*philo;

	philo = (t_philo *)ph;
	print("is thinking\n", time_ms() - philo->var->time_zero, \
		philo->id + 1, philo);
	if ((philo->id) % 2 == 1)
		ft_usleep(100, philo);
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = time_ms();
	pthread_mutex_unlock(&philo->m_last_meal);
	while (1)
	{
		pthread_mutex_lock(&philo->var->print);
		if (philo->var->dead == 1)
			break ;
		pthread_mutex_unlock(&philo->var->print);
		id = philo->id;
		if (id == philo->var->number_of_philosophers - 1)
			next_id = 0;
		else
			next_id = id + 1;
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
		ft_usleep(philo->var->time_to_sleep, \
			philo);
		print("is thinking\n", time_ms() - philo->var->time_zero, \
			philo->id + 1, philo);
	}
	return (0);
}

void	var_init(t_var *v, char **argv, int argc)
{
	t_var	*var;
	int		i;

	i = -1;
	var = (t_var *)v;
	var->number_of_philosophers = ft_atoi(argv[1]);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	var->time_zero = time_ms();
	pthread_mutex_init(&var->m_dead, NULL);
	var->dead = 0;
	pthread_mutex_init(&var->print, NULL);
	pthread_mutex_init(&var->m_everyone_ate, NULL);
	var->everyone_ate = 0;
	var->fork = malloc(sizeof(pthread_mutex_t) * var->number_of_philosophers);
	while (++i < var->number_of_philosophers)
		pthread_mutex_init(&var->fork[i], NULL);
	if (argc == 6)
		var->must_eat = ft_atoi(argv[5]);
	else
		var->must_eat = -1;
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_var		var;
	pthread_t	*thread;
	pthread_t	checker;
	int			i;

	i = -1;
	if (check_arg(argc, argv))
		return (0);
	var_init(&var, argv, argc);
	thread = malloc(sizeof(pthread_t) * var.number_of_philosophers);
	philo = malloc(sizeof(t_philo) * (var.number_of_philosophers));
	while (++i < var.number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].nb_meal = 0;
		philo[i].var = &var;
		philo[i].last_meal = philo[i].var->time_zero;
		pthread_mutex_init(&philo[i].m_last_meal, NULL);
	}
	i = -1;
	pthread_mutex_lock(&var.m_dead);
	while (++i < var.number_of_philosophers)
		pthread_create(&thread[i], NULL, philo_routine, (void *)&philo[i]);
	pthread_create(&checker, NULL, philo_checker, (void *)philo);
	pthread_join(checker, NULL);
	pthread_mutex_lock(&var.m_dead);
}

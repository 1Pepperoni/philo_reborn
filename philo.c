/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pory <pory@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:43:36 by ory               #+#    #+#             */
/*   Updated: 2023/02/15 12:58:03 by pory             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ph)
{
	int		id;
	int		next_id;
	t_philo	*philo;

	philo = (t_philo *)ph;
	print("is thinking\n", time_ms() - philo->var->time_zero, \
		philo->id + 1, philo);
	last_meal(philo);
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
		eats(philo, next_id, id);
		min_eats(philo);
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

void	init_philo(t_philo *ph, t_var *var)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)ph;
	i = 0;
	while (i < var->number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].nb_meal = 0;
		philo[i].var = var;
		philo[i].last_meal = philo[i].var->time_zero;
		pthread_mutex_init(&philo[i].m_last_meal, NULL);
		i++;
	}
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
	init_philo(philo, &var);
	i = -1;
	pthread_mutex_lock(&var.m_dead);
	while (++i < var.number_of_philosophers)
		pthread_create(&thread[i], NULL, philo_routine, (void *)&philo[i]);
	pthread_create(&checker, NULL, philo_checker, (void *)philo);
	pthread_join(checker, NULL);
	pthread_mutex_lock(&var.m_dead);
}

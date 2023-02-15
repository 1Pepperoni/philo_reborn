/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pory <pory@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:43:36 by ory               #+#    #+#             */
/*   Updated: 2023/02/15 08:17:09 by pory             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_everyone_ate(t_philo *philo)
{
	// int i;
	// int	check;

	// i = -1;
	// check = -1;
	// while (++i < philo->var->number_of_philosophers)
	// {
	// 	if (philo->var->everyone_ate[i] == 1)
	// 		check++;
	// }
	// if (check == philo->var->number_of_philosophers - 1)
	// 	return (1);
	// return (0);

	//pthread_mutex_lock(&philo->var->m_everyone_ate);
	pthread_mutex_lock(&philo->m_last_meal);
        pthread_mutex_lock(&philo->var->print);
	pthread_mutex_lock(&philo->var->m_everyone_ate);
	if (philo->var->everyone_ate == philo->var->number_of_philosophers)
	{
		//pthread_mutex_unlock(&philo->m_last_meal);
		//pthread_mutex_unlock(&philo->var->m_everyone_ate);
		//pthread_mutex_unlock(&philo->var->m_dead2);
		return(1);
	}
	else	
	{
                pthread_mutex_unlock(&philo->m_last_meal);
                pthread_mutex_unlock(&philo->var->print);
		pthread_mutex_unlock(&philo->var->m_everyone_ate);
        }
	return(0);

}

int	last_meal_time_calc(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_last_meal);
        pthread_mutex_lock(&philo->var->print);
	if ((int)time_ms() - (int)philo->last_meal >= (int)philo->var->time_to_die)
	{
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->m_last_meal);
                pthread_mutex_unlock(&philo->var->print);
	}
	return (0);
}

void	*philo_checker(void *ph)
{
	t_philo	*philo;
	int		i;
	unsigned long	time;
	int	bowling;
	int triche;

	//int		j;

	philo = (t_philo *)ph;
	bowling = 0;
	if(philo->var->time_to_sleep < philo->var->time_to_eat)
	{
		bowling = 1;
	}
	if (bowling == 1)
	{
		triche = 13;
	}
	else
		triche = -13;
	
	
	i = 0;
	//j = -1;
	while (1)
	{
        pthread_mutex_lock(&philo[i].m_last_meal);
        pthread_mutex_lock(&philo[i].var->print);
	    pthread_mutex_lock(&philo[i].var->m_everyone_ate);
		//if (last_meal_time_calc(philo))
        if ((int)time_ms() - (int)philo[i].last_meal >= (int)philo[i].var->time_to_die)
		{
                        //printf("aaaaaaaaaaaaaa\n");
			philo[i].var->dead = 1;
			//pthread_mutex_unlock(&philo[i].var->m_dead);
			//pthread_mutex_lock(&philo[i].var->print);
			//pthread_mutex_lock(&philo->var->print);

			// time = time_ms() - philo[i].var->time_zero;
			// if (philo[i].var->time_to_sleep > philo[i].var->time_to_eat)
			// {
			// 	usleep(philo[i].var->time_to_die);
			// 	printf("%lu ms %d is dead\n", time, philo[i].id + 1);
			// 	printf("pedofile\n");
			// }
			// else
			// 	printf("%lu ms %d is dead\n", time + 200, philo[i].id + 1);

			time = time_ms() - philo[i].var->time_zero;
			//if (philo[i].var->time_to_sleep > philo[i].var->time_to_eat)
			//	time = time - philo[i].var->time_to_eat;
			/*if (philo[i].var->time_to_sleep > philo[i].var->time_to_eat)
				time = time + philo[i].var->time_to_eat;*/
			printf("%lu ms %d is dead\n", time, philo[i].id + 1);
                        // i = -1;
                        // while(++i < philo->var->number_of_philosophers)
                        //         pthread_mutex_destroy(&philo->var->fork[i]);
            pthread_mutex_unlock(&philo[i].var->print);
			pthread_mutex_unlock(&philo[i].var->m_dead);
			sleep(3);
			return (0);
		}
		//else if (check_everyone_ate(philo))
        else if (philo[i].var->everyone_ate == philo[i].var->number_of_philosophers)
		{
			// pthread_mutex_lock(&philo[i].var->print);
			// philo[i].var->dead = 2;
			//pthread_mutex_lock(&philo->var->print);
			sleep(1);
            pthread_mutex_unlock(&philo[i].var->m_dead);
			//pthread_mutex_unlock(&philo[i].var->m_dead);
			//pthread_mutex_unlock(&philo->var->m_dead2);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].m_last_meal);
        pthread_mutex_unlock(&philo[i].var->print);
	    pthread_mutex_unlock(&philo[i].var->m_everyone_ate);
		if (i == philo[i].var->number_of_philosophers - 1)
			i = -1;
		//pthread_mutex_unlock(&philo[i].m_last_meal);
		// pthread_mutex_unlock(&philo[i].var->m_dead);
		i++;
                //usleep(1000);
	}
}

void	print(char *str, unsigned long time, int id, t_philo *philo)
{
	pthread_mutex_lock(&philo->var->print);
    if (philo->var->dead != 1)
	{
		printf("%lu ms %d %s", time, id, str);
		pthread_mutex_unlock(&philo->var->print);
	}
}

// void	acces_forks(t_philo *philo)
// {
	
// }

void	*philo_routine(void *ph)
{
	int		id;
	int		next_id;
	t_philo	*philo;
	long long time_to_think;

	philo = (t_philo *)ph;
    if ((philo->id) % 2 == 1)
        ft_usleep(100, philo);
	//else if((philo->id) % 2 == 1)
	//	usleep(5000);
	//{
	//	
	//}
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
		print("has taken a fork\n", time_ms() - philo->var->time_zero, philo->id + 1, philo);
		pthread_mutex_lock(&philo->var->fork[next_id]);
		print("has taken a fork\n", time_ms() - philo->var->time_zero, philo->id + 1, philo);
		print("is eating\n", time_ms() - philo->var->time_zero, philo->id + 1, philo);
		pthread_mutex_lock(&philo->m_last_meal);
		philo->nb_meal++;
		pthread_mutex_unlock(&philo->m_last_meal);
		philo->last_meal = time_ms();
		ft_usleep(philo->var->time_to_eat, philo);
		pthread_mutex_unlock(&philo->var->fork[id]);
		pthread_mutex_unlock(&philo->var->fork[next_id]);
		//philo_sleep(philo->var->time_to_eat * 1000, philo);
		//philo_sleep2(philo->var->time_to_eat * 1000);
		pthread_mutex_lock(&philo->m_last_meal);
		if ((int)philo->nb_meal == philo->var->must_eat)
		{
			pthread_mutex_lock(&philo->var->m_everyone_ate);
			philo->var->everyone_ate++;
			//pthread_mutex_unlock(&philo->m_last_meal);
			pthread_mutex_unlock(&philo->var->m_everyone_ate);
		}
		// else
		// 	pthread_mutex_unlock(&philo->m_last_meal);
		// pthread_mutex_lock(&philo->m_last_meal);
		// philo->last_meal = time_ms();
		//printf("last meal philo[%d] = %d\n", philo->id, (int)time_ms() - (int)philo->last_meal);
		// pthread_mutex_lock(&philo->var->print);
		// if (philo->var->dead == 1)
		// 	break ;
		// pthread_mutex_unlock(&philo->var->print);
		pthread_mutex_unlock(&philo->m_last_meal);
		print("is sleeping\n", time_ms() - philo->var->time_zero, philo->id + 1, philo);
		ft_usleep(philo->var->time_to_sleep, philo);
		//philo_sleep(philo->var->time_to_sleep * 1000, philo);
		//philo_sleep2(philo->var->time_to_sleep * 1000);
		// if (time_ms() - philo->last_meal < philo->var->time_to_eat)
		// {
		// 	//printf("amongus %d\n", philo->id);
		// 	usleep(200);
		// }
		print("is thinking\n", time_ms() - philo->var->time_zero, philo->id + 1, philo);
		time_to_think = (philo->var->time_to_die - (time_ms() - philo->last_meal) - philo->var->time_to_eat) / 2;
		//printf("philo : %d time_to_think = %lld\n", id + 1, time_to_think);
		//usleep(time_to_think * 1000);
	}
	return (0);
}

void	var_init(t_var *v, char **argv, int argc)
{
	t_var	*var;
        int i;

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
        while(++i < var->number_of_philosophers)
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

	// usleep(100000);
	// printf("usigned long long : %llu\n", (unsigned long long)time_ms());
	// printf("usigned long : %lu\n", time_ms());
	// printf("int : %d\n", (int)time_ms());
	// exit (0);
	i = -1;
        if (check_arg(argc, argv))
		return(0);
	var_init(&var, argv, argc);
        thread = malloc(sizeof(pthread_t) * var.number_of_philosophers);
	philo = malloc(sizeof(t_philo) * (var.number_of_philosophers));
	while (++i < var.number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].nb_meal = 0;
		//philo[i].dead = 0;
		philo[i].var = &var;
		philo[i].last_meal = philo[i].var->time_zero;
		//philo[i].fork = fork;
		pthread_mutex_init(&philo[i].m_last_meal, NULL);
		//pthread_mutex_init(&philo[i].fork[i].fork, NULL);
	}
	i = -1;
    pthread_mutex_lock(&var.m_dead);
	while (++i < var.number_of_philosophers)
	{
		pthread_create(&thread[i], NULL, philo_routine, (void *)&philo[i]);
		//usleep(1000);
	}
        // i = -1;
        // while (++i < var.number_of_philosophers)
	// 	pthread_join(thread[i], NULL);
	pthread_create(&checker, NULL, philo_checker, (void *)philo);
	pthread_join(checker, NULL);
	pthread_mutex_lock(&var.m_dead);
}
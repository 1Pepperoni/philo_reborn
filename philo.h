/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ory <ory@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:12:18 by pory              #+#    #+#             */
/*   Updated: 2023/02/11 00:59:06 by ory              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct	s_var
{
	int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned long int	time_zero;
	int					must_eat;
	pthread_mutex_t		print;
	pthread_mutex_t		m_dead;
	int				everyone_ate;
	pthread_mutex_t			m_everyone_ate;
	int					dead;
	pthread_mutex_t		*fork;
}				t_var;

typedef struct	s_philo
{
	int		id;
	int		nb_meal;
	int		dead;
	int		last_meal;
	pthread_mutex_t	m_last_meal;
	int		diff_time_meal;
	t_var	*var;
}				t_philo;


int	ft_atoi(const char *str);
int	ft_isdigit(int c);
unsigned long int	time_ms(void);
void	print(char *str, unsigned long time, int id, t_philo *philo);
int	check_arg(int argc, char **argv);
int	digit_check(char *str);





int		check_everyone_ate(t_philo *philo);
//void	philo_sleep(unsigned long time_to_sleep, t_philo *philo);
int	death_stop(t_philo *philo);
void	philo_sleep2(unsigned long time_to_sleep);

void	philo_sleep(unsigned long time_to_sleep, t_philo *philo);





#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:48:41 by cwastche          #+#    #+#             */
/*   Updated: 2022/03/16 09:48:43 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	eat(t_philo *philo)
{
	int	l_fork;
	int	r_fork;

	l_fork = philo->id - 1;
	r_fork = philo->id % philo->data->nb_of_philos;
	pthread_mutex_lock(&philo->data->fork[l_fork]);
	print_msg(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->fork[r_fork]);
	print_msg(philo, "has taken a fork\n");
	print_msg(philo, "is eating\n");
	pthread_mutex_lock(&philo->data->print);
	philo->time_of_last_meal = get_time();
	pthread_mutex_unlock(&philo->data->print);
	if (philo->data->time_to_die < philo->data->time_to_eat)
		ft_sleep(philo->data->time_to_die, philo->data->nb_of_philos);
	else
		ft_sleep(philo->data->time_to_eat, philo->data->nb_of_philos);
	pthread_mutex_unlock(&philo->data->fork[l_fork]);
	pthread_mutex_unlock(&philo->data->fork[r_fork]);
	return ;
}

void	think_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping\n");
	ft_sleep(philo->data->time_to_sleep, philo->data->nb_of_philos);
	print_msg(philo, "is thinking\n");
}

int	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->philo_died)
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

void	*routine(void	*routine_input)
{
	t_philo		*philo;
	int			max_meals;

	max_meals = 0;
	philo = routine_input;
	if (philo->id % 2 == 0)
		ft_sleep(philo->data->time_to_eat / 2, philo->data->nb_of_philos);
	while (!max_meals)
	{
		if (philo_died(philo))
			break ;
		eat(philo);
		philo->number_of_meals++;
		if (philo->number_of_meals == philo->data->number_of_max_meals)
		{
			pthread_mutex_lock(philodata->print);
			philo->data->ate_max_meals += 1;
			pthread_mutex_unlock(&data->print);
			max_meals = 1;
		}
		
		think_sleep(philo);
	}
	return (0);
}

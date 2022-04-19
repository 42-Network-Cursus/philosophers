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
	philo->time_of_last_meal = get_time();
	if (philo->data->time_to_die < philo->data->time_to_eat)
		ft_sleep(philo->data->time_to_die, philo->data->nb_of_philos);
	else
		ft_sleep(philo->data->time_to_eat, philo->data->nb_of_philos);
	pthread_mutex_unlock(&philo->data->fork[l_fork]);
	pthread_mutex_unlock(&philo->data->fork[r_fork]);
	return ;
}

void	*routine(void	*routine_input)
{
	t_philo		*philo;
	int			max_meals;

	max_meals = 0;
	philo = routine_input;
	philo[id->time_of_last_meal = philo->data->time_at_launch;
	if (philo->id % 2 == 0)
		ft_sleep(philo->data->time_to_eat / 2, philo->data->nb_of_philos);
	while (!philo->data->philo_died && !max_meals)
	{	
		eat(philo);
		philo->number_of_meals++;
		if (philo->number_of_meals == philo->data->number_of_max_meals)
		{
			philo->data->ate_max_meals += 1;
			max_meals = 1;
		}
		print_msg(philo, "is sleeping\n");
		ft_sleep(philo->data->time_to_sleep, philo->data->nb_of_philos);
		print_msg(philo, "is thinking\n");
	}
	return (0);
}

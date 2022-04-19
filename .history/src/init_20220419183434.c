/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:48:27 by cwastche          #+#    #+#             */
/*   Updated: 2022/03/16 09:48:29 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	params_init(char **av, t_data *data)
{
	data->nb_of_philos = ft_atoi(av[1]);
	if (data->nb_of_philos < 1)
		return (error("Error\nInvalid number of philosophers\n"));
	data->time_to_die = ft_atoi(av[2]);
	if (data->time_to_die < 1)
		return (error("Error\nInvalid time to die\n"));
	data->time_to_eat = ft_atoi(av[3]);
	if (data->time_to_eat < 1)
		return (error("Error\nInvalid time to eat\n"));
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_sleep < 1)
		return (error("Error\nInvalid time to sleep\n"));
	if (av[5])
	{
		data->number_of_max_meals = ft_atoi(av[5]);
		if (data->number_of_max_meals < 1)
			return (error("Error\nInvalid number of meals\n"));
	}
	else
		data->number_of_max_meals = -1;
	if (pthread_mutex_init(&data->print, NULL))
		return (error("Error\nMutex init failed\n"));
	data->philo_died = 0;
	return (0);
}

int	philos_init(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	data->ate_max_meals = 0;
	pthread_mutex_lock(&philo->data->print);
	while (++i < data->nb_of_philos)
	{
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].number_of_meals = 0;
		philo[i].time_of_last_meal = philo->data->time_at_launch;
		if (pthread_mutex_init(&data->fork[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->fork[i]);
			return (error("Error\nMutex init failed\n"));
		}
		pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]);
	}
	return (0);
}

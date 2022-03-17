/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:48:34 by cwastche          #+#    #+#             */
/*   Updated: 2022/03/16 09:48:35 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	free_and_destroy(t_philo *philo, t_data *data)
{
	int	i;

	if (data->nb_of_philos == 1)
		pthread_mutex_unlock(&data->fork[0]);
	i = -1;
	while (++i < data->nb_of_philos)
	{
		pthread_join(philo[i].thread_id, NULL);
		pthread_mutex_destroy(&data->fork[i]);
	}
	pthread_mutex_destroy(&data->print);
	free(data->fork);
	free(philo);
}

void	loop_until_death(t_philo *philo, t_data *data)
{
	int		i;
	size_t	last_meal;

	while (!data->start)
		continue ;
	while (!data->philo_died)
	{
		i = -1;
		while (++i < data->nb_of_philos && !data->philo_died)
		{
			last_meal = get_time() - philo[i].time_of_last_meal;
			if ((int)last_meal > data->time_to_die)
			{
				print_msg(philo, "has died.\n");
				data->philo_died = 1;
			}
			if (philo[data->nb_of_philos - 1].ate_max_meals == 1)
			{
				data->philo_died = 1;
				break ;
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	data;

	if (ac != 5 && ac != 6)
		return (error("Error\nWrong number of arguments\n"));
	if (params_init(av, &data))
		return (1);
	philo = malloc(sizeof(t_philo) * data.nb_of_philos);
	if (!philo)
	{
		pthread_mutex_destroy(&data->print);
		return (error("Error\nMalloc failed\n"));
	}
	data.fork = malloc(sizeof(pthread_mutex_t) * data.nb_of_philos);
	if (!data.fork)
	{
		pthread_mutex_destroy(&data->print);
		free(philo);
		return (error("Error\nMalloc failed\n"));
	}
	philos_init(philo, &data);
	loop_until_death(philo, &data);
	free_and_destroy(philo, &data);
	return (0);
}

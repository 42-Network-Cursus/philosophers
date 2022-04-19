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
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < data->nb_of_philos)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(&data->print);
	free(data->fork);
	free(philo);
}

void	death_print(t_philo *philo, t_data *data)
{
	size_t	time;

	time = get_time() - philo->data->time_at_launch;
	printf("%zu %d has died.\n", time, philo->id);
	data->philo_died = 1;
	pthread_mutex_unlock(&data->print);
}

void	loop_until_death(t_philo *philo, t_data *data)
{
	int		i;
	size_t	last_meal;

	while (!data->philo_died)
	{
		i = -1;
		while (++i < data->nb_of_philos && !data->philo_died)
		{
			pthread_mutex_lock(&data->print);
			last_meal = get_time() - philo[i].time_of_last_meal;
			if ((int)last_meal > data->time_to_die)
			{
				death_print(philo, data);
				break ;
			}
			if (data->ate_max_meals == data->nb_of_philos)
			{
				data->philo_died = 1;
				pthread_mutex_unlock(&data->print);
				break ;
			}
			pthread_mutex_unlock(&data->print);
		}
	}
}

void	ft_free(int nb, t_data *data, t_philo *philo)
{
	if (nb < 3)
		pthread_mutex_destroy(&data->print);
	if (nb < 2)
		free(philo);
	if (nb < 1)
		free(data->fork);
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
		return (ft_free(2, &data, philo), error("Error\nMalloc failed\n"));
	data.fork = malloc(sizeof(pthread_mutex_t) * data.nb_of_philos);
	if (!data.fork)
		return (ft_free(1, &data, philo), error("Error\nMalloc failed\n"));
	if (philos_init(philo, &data))
		return (ft_free(0, &data, philo),1);
	loop_until_death(philo, &data);
	free_and_destroy(philo, &data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:48:58 by cwastche          #+#    #+#             */
/*   Updated: 2022/03/16 09:48:59 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	error(char *msg)
{
	printf("%s", msg);
	return (1);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_sleep(size_t time, size_t time_to_wait)
{
	while ((get_time() - time) < time_to_wait)
		usleep(50);
}

void	print_msg(t_philo *philo, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->time_at_launch;
	if (!philo->data->philo_died)
		printf("%zu %d %s", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

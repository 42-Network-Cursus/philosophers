/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwastche <cwastche@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:48:19 by cwastche          #+#    #+#             */
/*   Updated: 2022/03/16 09:48:21 by cwastche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_LONG 9223372036854775807 //Used by atoi

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //pthread + mutex

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	size_t			time_at_launch;
	int				start;
	int				nb_of_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				number_of_max_meals;
	int				philo_died;
}				t_data;

typedef struct s_philosopher
{
	pthread_t		thread_id;
	t_data			*data;
	size_t			time_of_last_meal;
	int				number_of_meals;
	int				id;
	int				ate_max_meals;
}				t_philo;

//	INIT
int		params_init(char **av, t_data *data);
void	philos_init(t_philo *philo, t_data *data);

//	MAIN
void	free_and_destroy(t_philo *philo, t_data *data);
void	loop_until_death(t_philo *philo, t_data *data);

//	ROUTINE
void	eat(t_philo *philo);
void	*routine(void	*function_input);

//	UTILS
int		ft_atoi(const char *str);
int		error(char *msg);
size_t	get_time(void);
void	ft_sleep(size_t time, size_t time_to_wait);
void	print_msg(t_philo *philo, char *msg);

#endif

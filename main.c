/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkord <gkord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:20:40 by iwhana            #+#    #+#             */
/*   Updated: 2022/06/14 18:31:41 by gkord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = data->nb_philo;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (data->nb_philo + 1));
	if (!data->forks)
		return (1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = data->nb_philo;
	data->philosophers = (t_philo *)malloc(sizeof (t_philo) * (data->nb_philo + 1));
	if (!data->philosophers)
		return (1);
	data->philosophers[data->nb_philo].id = -1;
	while (--i >= 0)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].x_ate = 0;
		data->philosophers[i].left_fork_id = i;
		data->philosophers[i].right_fork_id = (i + 1) % data->nb_philo;
		data->philosophers[i].t_last_meal = 0;
		data->philosophers[i].data = data;
	}
	return (0);
}

void	exit_program(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	free(data->forks);
	free(data->philosophers);
	pthread_mutex_destroy(&(data->writing));
}

static void	parse_must_eat(t_data *data, char **argv)
{
	if (argv[5])
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat <= 0)
			return ;
	}
	else
		data->must_eat = -1;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (1);
	data.nb_philo = ft_atoi(argv[1]);
	data.time_death = ft_atoi(argv[2]);
	data.time_eat = ft_atoi(argv[3]);
	data.time_sleep = ft_atoi(argv[4]);
	data.all_ate = 0;
	data.dieded = 0;
	if (data.nb_philo < 1 || data.time_death < 0 || data.time_eat < 0
		|| data.time_sleep < 0)
		return (1);
	parse_must_eat(&data, argv);
	if (init_mutex(&data))
		return (2);
	if (init_philosophers(&data))
		return (2);
	if (philosophers(&data))
		return (1);
	return (0);
}

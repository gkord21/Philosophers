/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkord <gkord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:19:34 by iwhana            #+#    #+#             */
/*   Updated: 2022/06/14 18:31:45 by gkord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eats(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
	action_print(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
	action_print(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->meal_check));
	action_print(data, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(data->meal_check));
	smart_sleep(data->time_eat, data);
	(philo->x_ate)++;
	pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
}

void	*p_thread(void *void_philo)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)void_philo;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (!(data->dieded))
	{
		philo_eats(philo);
		if (data->all_ate)
			break ;
		action_print(data, philo->id, "is sleeping");
		smart_sleep(data->time_sleep, data);
		action_print(data, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	death_help(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (data->must_eat != -1 && i < data->nb_philo
		&& philo[i].x_ate >= data->must_eat)
		i++;
	if (i == data->nb_philo)
		data->all_ate = 1;
}

void	death_check(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->all_ate))
	{
		i = -1;
		while (++i < data->nb_philo && !(data->dieded))
		{
			pthread_mutex_lock(&(data->meal_check));
			if (time_diff(philo[i].t_last_meal, timestamp())
				> data->time_death)
			{
				action_print(data, i, "died");
				data->dieded = 1;
			}
			pthread_mutex_unlock(&(data->meal_check));
			usleep(100);
		}
		if (data->dieded)
			break ;
		death_help(data, data->philosophers);
	}
}

int	philosophers(t_data *data)
{
	int			i;
	t_philo		*phi;

	i = 0;
	phi = data->philosophers;
	data->first_timestamp = timestamp();
	while (i < data->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		i++;
	}
	death_check(data, data->philosophers);
	exit_program(data, phi);
	return (0);
}

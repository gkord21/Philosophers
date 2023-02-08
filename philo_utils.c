/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkord <gkord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:59:07 by iwhana            #+#    #+#             */
/*   Updated: 2022/06/14 17:48:08 by gkord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_data *data)
{
	long long	i;

	i = timestamp();
	while (!(data->dieded))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	action_print(t_data *data, int id, char *string)
{
	pthread_mutex_lock(&(data->writing));
	if (!(data->dieded))
	{
		printf("%lli ", timestamp() - data->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(data->writing));
	return ;
}

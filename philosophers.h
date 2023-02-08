/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkord <gkord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:15:04 by gkord             #+#    #+#             */
/*   Updated: 2022/06/14 17:52:12 by gkord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

struct	s_philo;

typedef struct s_philo
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_data		*data;
	pthread_t			thread_id;
}	t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing;
	t_philo				*philosophers;
}	t_data;

int			ft_atoi(const char *str);
void		action_print(t_data *data, int id, char *string);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		smart_sleep(long long time, t_data *data);
int			philosophers(t_data *data);
void		exit_program(t_data *data, t_philo *philo);
void		death_help(t_data *data, t_philo *philo);

#endif

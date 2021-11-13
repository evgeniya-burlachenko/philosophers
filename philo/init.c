/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:28:32 by skelly            #+#    #+#             */
/*   Updated: 2021/11/13 05:03:32 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_argv(int argc, char **argv, t_philo *philo)
{
	philo->nbr = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleap = ft_atoi(argv[4]);
	philo->all_alive = 1;
	if (argc == 6)
		philo->count_eat = ft_atoi(argv[5]);
	else
		philo->count_eat = -1;
	if (philo->nbr < 1 || philo->time_to_sleap < 0 || philo->time_to_eat < 0
		|| philo->time_to_sleap < 0 || (argc == 6 && philo->count_eat <= 0))
		return (printf(YELLOW ERR_USAGE_2));
	return (0);
}

int	init_mutex(t_philo	*philo)
{
	int	i;

	philo->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * philo->nbr);
	if (!(philo->forks))
		return (printf(RED ERR_MALLOC));
	i = -1;
	while (++i < philo->nbr)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL))
			return (printf(RED ERR_MUTEX));
	}
	if (pthread_mutex_init(&philo->eat, NULL))
		return (printf(RED ERR_MUTEX));
	return (0);
}

int	init_philosophers(t_philo *philo)
{
	int	i;

	philo->one = (t_one *)malloc(sizeof(t_one) * philo->nbr);
	if (!(philo->one))
		return (printf(RED ERR_MALLOC));
	i = -1;
	while (++i < philo->nbr)
	{
		philo->one[i].id = i;
		philo->one[i].count = 0;
		philo->one[i].time_last_meal = 0;
		philo->one[i].philo = philo;
		philo->one[i].left_fork = &philo->forks[i];
		if (i < philo->nbr - 1)
			philo->one[i].right_fork = &philo->forks[i + 1];
		else
			philo->one[i].right_fork = &philo->forks[0];
	}
	return (0);
}

void	check_count_eat(t_philo *philo, t_one *one)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < philo->nbr)
	{
		if (one[i].count >= philo->count_eat)
			count++;
	}
	if (count == philo->nbr)
		philo->all_alive = 0;
}

long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

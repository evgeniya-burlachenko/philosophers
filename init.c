/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:28:32 by skelly            #+#    #+#             */
/*   Updated: 2021/11/09 19:51:44 by skelly           ###   ########.fr       */
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
		return (printf(ERR_USAGE_2));
	if (philo->nbr == 1)
		return (printf(ERR_COUNT_1));
	return (0);
}

int	init_mutex(t_philo	*philo)
{
	int	i;
	if (!(philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->nbr)))
		return (printf(ERR_MALLOC));
	i = -1;
	while (++i < philo->nbr)
		pthread_mutex_init(&philo->forks[i], NULL);
	pthread_mutex_init(&philo->eat, NULL);
	pthread_mutex_init(&philo->print, NULL);
	return (0);
}

int init_philosophers(t_philo	*philo)
{
	int	i;
	
	if(!(philo->one = malloc(sizeof(t_one) * philo->nbr)))
		return (printf(ERR_MALLOC));
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
			philo->one[i].right_fork= &philo->forks[0];
	}
	return (0);
}


void free_all(t_philo *philo, t_one *one)
{
	int i;
	
	i = -1;
	while (++i < philo->nbr)
		pthread_join(one[i].tid, NULL);
	i = -1;
	while (++i < philo->nbr)
		pthread_mutex_destroy(&philo->forks[i]);
	pthread_mutex_destroy(&philo->eat);
	pthread_mutex_destroy(&philo->print);
	free(philo->forks);
	free(philo->one);
}
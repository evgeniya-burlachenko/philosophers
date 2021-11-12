/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:42:06 by skelly            #+#    #+#             */
/*   Updated: 2021/11/12 11:19:16 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_one	*one)
{
	t_philo	*philo;

	philo = one->philo;
	sem_wait(one->philo->forks);
	printf("%ld %d %s\n", get_time() - philo->start_time,
		one->id + 1, "has taken a fork");
	sem_wait(one->philo->forks);
	printf("%ld %d %s\n", get_time() - philo->start_time,
		one->id + 1, "has taken a fork");
	sem_wait(philo->eat);
	printf("%ld %d %s\n", get_time() - philo->start_time,
		one->id + 1, "is eating");
	one->time_last_meal = get_time() - philo->start_time;
	sem_post(philo->eat);
	usleep(philo->time_to_eat * 900);
	one->count += 1;
	sem_post(one->philo->forks);
	sem_post(one->philo->forks);
}

void	*start_sim(void	*one_phil)
{
	t_one	*one;
	t_philo	*philo;

	one = (t_one *)one_phil;
	philo = one->philo;
	if (one->id % 2)
		usleep(20000);
	while (philo->all_alive)
	{
		eat(one);
		if (philo->all_alive)
			printf("%ld %d %s\n", get_time() - philo->start_time,
				one->id + 1, "is sleeping");
		usleep(philo->time_to_sleap * 1000);
		if (philo->all_alive)
			printf("%ld %d %s\n", get_time() - philo->start_time,
				one->id + 1, "is thinking");
	}
	exit (0);
}

void	stop_sim(t_philo *philo, t_one *one)
{
	int	i;
	int	count;

	while (philo->all_alive)
	{
		i = -1;
		while (++i < philo->nbr && philo->all_alive)
		{
			sem_wait(philo->eat);
			if (get_time() - philo->start_time - one[i].time_last_meal
				> philo->time_to_die)
			{
				if (philo->all_alive)
					printf(RED"%ld %d %s\n", get_time() - philo->start_time,
						one->id + 1, "died");
				philo->all_alive = 0;
			}
			sem_post(philo->eat);
			usleep(100);
		}
		if (philo->count_eat != -1 && philo->all_alive)
			check_count_eat(philo, one);
	}
}

int	simulate(t_philo *philo)
{
	int		i;
	t_one	*one;
	int		count;

	i = -1;
	one = philo->one;
	philo->start_time = get_time();
	while (++i < philo->nbr)
	{
		if (pthread_create(&one[i].tid, NULL, start_sim, &one[i]))
			return (printf(ERR_MUTEX_2));
	}
	stop_sim(philo, philo->one);
	free_all(philo, philo->one);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		philo;

	if (argc < 5 || argc > 6)
		return (printf(ERR_USAGE));
	if (parse_argv(argc, argv, &philo))
		return (1);
	if (!(check_argv(argv)))
		return (0);
	if (init_philosophers(&philo))
		return (1);
	if (init_mutex(&philo))
		return (1);
	if (simulate(&philo))
		return (1);
	return (0);
}

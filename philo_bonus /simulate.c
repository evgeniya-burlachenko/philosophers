/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:46:32 by skelly            #+#    #+#             */
/*   Updated: 2021/11/12 23:02:41 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo)
{	
	int	i;
	int	j;
	int	f;

	i = -1;
	while (++i < philo->nbr)
	{
		waitpid(-1, &f, 0);
		if (f != 0)
		{
			j = -1;
			while (++j < philo->nbr)
				kill(philo->one[j].id, 15);
			break ;
		}
	}
	sem_close(philo->eat);
	sem_close(philo->forks);
	sem_unlink("/philo_eat");
	sem_unlink("/philo_forks");
	free(philo->one);
}

void	eat(t_one	*one)
{
	t_philo	*philo;

	philo = one->philo;
	sem_wait(philo->forks);
	if (philo->all_alive)
		printf("%ld %d %s\n", get_time() - philo->start_time,
			one->id + 1, "has taken a fork");
	sem_wait(philo->forks);
	if (philo->all_alive)
		printf("%ld %d %s\n", get_time() - philo->start_time,
			one->id + 1, "has taken a fork");
	sem_wait(philo->eat);
	if (philo->all_alive)
		printf("%ld %d %s\n", get_time() - philo->start_time,
			one->id + 1, "is eating");
	one->time_last_meal = get_time() - philo->start_time;
	sem_post(philo->eat);
	usleep(philo->time_to_eat * 900);
	one->count += 1;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	*start_sim(void	*one_phil)
{
	t_one	*one;
	t_philo	*philo;

	one = (t_one *)one_phil;
	philo = one->philo;
	if (one->id % 2)
		ft_usleep(philo->time_to_sleap / 2);
	while (philo->all_alive)
	{
		eat(one);
		if (philo->all_alive)
			printf("%ld %d %s\n", get_time() - philo->start_time,
				one->id + 1, "is sleeping");
		ft_usleep(philo->time_to_sleap);
		if (philo->all_alive)
			printf("%ld %d %s\n", get_time() - philo->start_time,
				one->id + 1, "is thinking");
	}
	exit (0);
}

void	stop_sim(t_philo *philo, t_one *one)
{
	int	i;

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
				exit(1);
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

	i = -1;
	one = philo->one;
	philo->start_time = get_time();
	while (++i < philo->nbr)
	{
		if (pthread_create(&one[i].tid, NULL, start_sim, &one[i]))
			return (printf(ERR_MUTEX_2));
	}
	stop_sim(philo, philo->one);
	free_all(philo);
	return (0);
}
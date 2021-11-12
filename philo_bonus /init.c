/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:28:32 by skelly            #+#    #+#             */
/*   Updated: 2021/11/12 12:43:04 by skelly           ###   ########.fr       */
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
	if (philo->nbr == 1)
		return (printf(YELLOW ERR_COUNT_1));
	return (0);
}

int	init_mutex(t_philo	*philo)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_eat");
	philo->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, philo->nbr);
	philo->eat = sem_open("/philo_eat", O_CREAT, S_IRWXU, 1);
	return (0);
}

int	init_philosophers(t_philo *philo)
{
	int	i;

	philo->one = malloc(sizeof(t_one) * philo->nbr);
	if (!(philo->one))
		return (printf(RED ERR_MALLOC));
	i = -1;
	while (++i < philo->nbr)
	{
		philo->one[i].id = i;
		philo->one[i].count = 0;
		philo->one[i].time_last_meal = 0;
		philo->one[i].philo = philo;
	}
	return (0);
}

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

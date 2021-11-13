/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:42:06 by skelly            #+#    #+#             */
/*   Updated: 2021/11/13 16:58:47 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo, t_one *one)
{
	int	i;

	i = -1;
	(void)one;
	while (++i < philo->nbr)
		pthread_join(one[i].tid, NULL);
	i = -1;
	while (++i < philo->nbr)
		pthread_mutex_destroy(&philo->forks[i]);
	pthread_mutex_destroy(&philo->eat);
	free(philo->forks);
	free(philo->one);
}

int	main(int argc, char **argv)
{
	t_philo		philo;

	if (argc < 5 || argc > 6)
		return (printf(YELLOW ERR_USAGE));
	if (parse_argv(argc, argv, &philo))
		return (1);
	if (!(check_argv(argv)))
		return (0);
	if (!(check_argv_2(&philo)))
		return (0);
	if (init_mutex(&philo))
		return (1);
	if (init_philosophers(&philo))
		return (1);
	if (simulate(&philo))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:42:06 by skelly            #+#    #+#             */
/*   Updated: 2021/11/12 22:47:32 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		philo;

	if (argc < 5 || argc > 6)
		return (printf(YELLOW ERR_USAGE));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:41:48 by skelly            #+#    #+#             */
/*   Updated: 2021/11/12 16:19:47 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c <= '9' && c >= '0');
}

int	ft_atoi(const char *str)
{
	long int		num;
	int				sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}	
	while (ft_isdigit(*str))
	{
		num = num * 10 + (int)*str - '0';
		str++;
	}
	return (num * sign);
}

long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

int	check_argv(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
			{
				printf(ERR_SYMBOL);
				return (0);
			}
		}
	}
	return (1);
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

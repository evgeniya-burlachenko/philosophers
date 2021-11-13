/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:41:48 by skelly            #+#    #+#             */
/*   Updated: 2021/11/13 05:03:26 by skelly           ###   ########.fr       */
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

int	check_argv_2(t_philo *philo)
{
	if (philo->nbr > 200)
		printf(YELLOW ERR_USAGE_2);
	else if (philo->time_to_die < 60 || philo->time_to_eat < 60
		|| philo->time_to_sleap < 60)
	{
		printf(YELLOW ERR_USAGE_2);
	}
	else
		return (1);
	return (0);
}

void	ft_usleep(int ms)
{
	long	time;

	time = get_time();
	usleep(ms * 920);
	while (get_time() < time + ms)
		usleep(ms * 3);
}

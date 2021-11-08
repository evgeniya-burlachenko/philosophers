/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:42:06 by skelly            #+#    #+#             */
/*   Updated: 2021/11/08 22:45:24 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int		init_mutex(t_philo	*philo);
void	eat(t_one	*one);
void	print_activity(int id, t_philo *philo, char *str);
void	print_death(int id, t_philo *philo, char *str);
void	eat(t_one	*one);
void	*sim(void	*one_phil);
void	stop_simulation(t_philo *philo, t_one *one);
int		parse_argv(int argc, char **argv, t_philo *philo);
int		init_philosophers(t_philo	*philo);
int		simulate (t_philo *philo);

void	print_activity(int id, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->print);
	if (philo->all_alive)
		printf("%ld %d %s\n", get_time() - philo->start_time, id + 1, str);
	pthread_mutex_unlock(&philo->print);
}

void	print_death(int id, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->print);
	if (philo->all_alive)
		printf(RED"%ld %d %s\n", get_time() - philo->start_time, id + 1, str);
	philo->all_alive = 0;
	pthread_mutex_unlock(&philo->print);
}

void	eat(t_one	*one)
{
	t_philo	*philo;

	philo = one->philo;
	pthread_mutex_lock(one->left_fork);
	print_activity(one->id, philo, "has taken a fork");
	
	pthread_mutex_lock(one->right_fork);
	print_activity(one->id, philo, "has taken a fork");
	
	pthread_mutex_lock(&philo->eat);
	print_activity(one->id, philo, "is eating");
	
	one->last_meal = get_time() - philo->start_time;
	
	pthread_mutex_unlock(&philo->eat);
	
	usleep(philo->time_to_eat * 1000);
	one->count += 1;
	pthread_mutex_unlock(one->left_fork);
	pthread_mutex_unlock(one->right_fork);
}

void	*sim(void	*one_phil)
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
		print_activity(one->id, philo, "is sleeping");
		usleep(philo->time_to_sleap * 1000);
		print_activity(one->id, philo, "is thinking");
		
	}
	return (NULL);
}

int	simulate (t_philo *philo)
{
	int		i;
	t_one	*one;
	int	countt;
	
	i = -1;
	one = philo->one;
	philo->start_time = get_time();
	while (++i < philo->nbr)
		pthread_create(&one[i].thread, NULL, sim, &one[i]);
	while (philo->all_alive)
	{
		i = -1;	
		while (++i < philo->nbr && philo->all_alive)
		{
			pthread_mutex_lock(&philo->eat);
			
			if (get_time() - philo->start_time - one[i].last_meal
				> philo->time_to_die)
				print_death(i, philo, "died");
				
			pthread_mutex_unlock(&philo->eat);
			usleep(100);
		}
		if (philo->count_eat != -1 && philo->all_alive)
		{
			i = -1;
			countt = 0;
			while (++i < philo->nbr)
			{
				if (one[i].count >= philo->count_eat)
				countt++;
			}
			if (countt == philo->nbr)
				philo->all_alive = 0;
		}	
	}
	i = -1;
	while (++i < philo->nbr)
		pthread_join(one[i].thread, NULL);
	i = -1;
	while (++i < philo->nbr)
		pthread_mutex_destroy(&philo->forks[i]);
	pthread_mutex_destroy(&philo->eat);
	pthread_mutex_destroy(&philo->print);
	free(philo->forks);
	free(philo->one);
	return (0);
}

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
	//
	if (!(philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nbr)))
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
	//выделяю память и инициализирую каждого философв
	if(!(philo->one = malloc(sizeof(t_one) * philo->nbr)))
		return (printf(ERR_MALLOC));
	i = -1;
	while (++i < philo->nbr)
	{
		philo->one[i].id = i;
		philo->one[i].count = 0;
		philo->one[i].last_meal = 0;
		philo->one[i].philo = philo;
		philo->one[i].left_fork = &philo->forks[i];
		if (i < philo->nbr - 1)
			philo->one[i].right_fork = &philo->forks[i + 1];
		else
			philo->one[i].right_fork= &philo->forks[0];
	}
	return (0);
}

int main (int argc, char **argv)
{
	t_philo		philo;
	
	if (argc < 5 || argc > 6)
		return (printf(ERR_USAGE));
	if (parse_argv(argc, argv, &philo))
		return (1);
	if (init_mutex(&philo))
		return (1);
	if (init_philosophers(&philo))
		return (1);
	if (simulate(&philo))
		return (1);
	return (0);
	
}
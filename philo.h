/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:20:35 by skelly            #+#    #+#             */
/*   Updated: 2021/11/09 19:49:18 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# define YELLOW	"\033[1;33m"
# define RED	"\033[1;31m"

# define ERR_USAGE		YELLOW "Error usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERR_COUNT_1	RED"The philosopher can't eat with one fork. He died.\n"
# define ERR_MALLOC		RED"Error: memory not allocated"
# define ERR_USAGE_2	RED"Error: Wrong arguments\n"
# define ERR_SYMBOL		YELLOW "Cannot use this symbol\n"


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef	struct 			s_one
{
	int					id;
	int					count;//кол-во приемов пищи
	long				time_last_meal;//time last meal
	
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	
	pthread_t			tid;
	struct s_philo		*philo;
	
}						t_one;

typedef	struct 			s_philo
{
	int					nbr;
	
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleap;
	int					count_eat;
	
	int					all_alive; //flag
	long				start_time;
	
	pthread_mutex_t		*forks;
	pthread_mutex_t		eat;
	pthread_mutex_t		print;
	
	t_one				*one;
}						t_philo;

int 	init_philosophers(t_philo	*philo);
int		init_mutex(t_philo	*philo);
int		parse_argv(int argc, char **argv, t_philo *philo);
void 	free_all(t_philo *philo, t_one *one);

long	get_time(void);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		check_argv(char **argv);
void	print_activity(int id, t_philo *philo, char *str);
void	print_death(int id, t_philo *philo, char *str);






#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:20:35 by skelly            #+#    #+#             */
/*   Updated: 2021/11/13 20:26:06 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define YELLOW			"\033[1;33m"
# define RED			"\033[1;31m"
# define GREEN			"\033[1;32m"
# define ERR_USAGE		 "Error usage: ./philo number_of_philosophers \
time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERR_USAGE_2	"Error: Wrong arguments\n"
# define ERR_SYMBOL		"Cannot use this symbol\n"
# define ERR_COUNT_1	"The philosopher can't eat with one fork. He died.\n"
# define ERR_MALLOC		"Error: memory not allocated"
# define ERR_MUTEX		"Error: mutex not initialized"
# define ERR_MUTEX_2	"Error: pthreade_create not worked"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>

typedef struct s_one
{
	int					id;
	int					count;
	long				time_last_meal;
	pid_t				tid;
	struct s_philo		*philo;
}						t_one;
typedef struct s_philo
{
	int					nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleap;
	int					count_eat;
	int					all_alive;
	long				start_time;
	sem_t				*forks;
	sem_t				*eat;
	t_one				*one;
}						t_philo;
//init
int						parse_argv(int argc, char **argv, t_philo *philo);
int						init_mutex(t_philo	*philo);
int						init_philosophers(t_philo	*philo);
void					check_count_eat(t_philo *philo, t_one *one);
//utils
int						ft_isdigit(int c);
int						ft_atoi(const char *str);
long					get_time(void);
int						check_argv(char **argv);
void					ft_usleep(int ms);
//simulate
void					free_all(t_philo *philo);
void					eat(t_one	*one);
void					*start_sim(void	*one_phil);
void					stop_sim(t_philo *philo, t_one *one);
int						simulate(t_philo *philo);
#endif
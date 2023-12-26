/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:57:36 by jolopez-          #+#    #+#             */
/*   Updated: 2023/12/19 21:03:40 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct args
{
	int				philo_number;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meals;
}	t_args;

typedef struct philo
{
	int				id;
	int				alredy_eaten;
	int				foods;
	int				*stop;
	long long		start_time;
	long long		last_food;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*defender;
	t_args			*args;
}	t_philo;

typedef struct data
{
	int				stop;
	int				philos_eaten;
	long long		start_time;
	long long		time;
	pthread_t		*philosopher;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*defender;
	t_philo			*philo;
}	t_data;

/*	File atoi.c	*/
int			ft_atoi(const char *str);

/*	File mem.c	*/
void		ft_mem_free(t_data *data);

/*	File philosophers.c	*/
int			main(int argc, char **argv);

/*	File routine.c	*/
void		*routine(void *arg);

/*	File structs.c	*/
int			ft_set_philo(t_args *args, t_data *data, const int i);
int			ft_init_data(t_args *args, t_data *data, int argc, char **argv);

/*	File threads.c	*/
int			ft_create_threads(t_args *args, t_data *data);
void		ft_delete_threads(t_args *args, t_data *data);

/*	File utils.c	*/
long long	ft_time(void);
void		ft_wait(int time);
int			ft_check_stop(t_args *args, t_data *data, const int i);
void		ft_print(t_philo *philo, char *msg);


#endif

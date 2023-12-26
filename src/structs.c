/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ardeiro <Ardeiro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:48:26 by Ardeiro           #+#    #+#             */
/*   Updated: 2023/12/26 23:51:14 by Ardeiro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*	This function sets the philo i.
	- inits the fork[i] mutex
	- inits the defender[i] mutex
	- inits the print_lock mutex
	- sets the philo values:
		* the common args for the program
		* the common start time
		* the id of the philo
		* the common stop status
		* the allocated fork[i] as the right_fork mutex
		* the allocated fork[i + 1] as the left_fork mutex (0 for last one)
		* the allocated defender[i] as the defender mutex
		* the allocated print_lock mutex as the philo print_lock mutex	
		* sets the flag already_eaten to 0
		* inits the number of foods made to 0	*/

int	ft_set_philo(t_args *args, t_data *data, const int i)
{
	if (pthread_mutex_init(&(data->forks[i]), NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(data->defender[i]), NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(data->print_lock[i]), NULL))
		return (EXIT_FAILURE);
	data->philo[i].args = args;
	data->philo[i].start_time = data->start_time;
	data->philo[i].id = i + 1;
	data->philo[i].stop = &(data->stop);
	data->philo[i].right_fork = &(data->forks[i]);
	data->philo[i].left_fork = &(data->forks[(i + 1) % (args->philo_number)]);
	data->philo[i].defender = &(data->defender[i]);
	data->philo[i].print_lock = data->print_lock;
	data->philo[i].alredy_eaten = 0;
	data->philo[i].foods = 0;
	return (EXIT_SUCCESS);
}

/*	This function initializes the data structures with the argument values:
	- number of philosophers
	- time to die
	- time to eat
	- time to sleep
	- if exists, the number of meals

	Then it allocates memory for:
	- the number of philosopher * t_philo philo
	- the number of philosopher * pthread_t philosopher
	- the number of philosopher * pthread_mutex_t forks
	- the number of philosopher * pthread_mutex_t defenders ()
	- 1 pthread_mutex_t print_locks (to allow or not to print)

	Finally it sets:
	- stop status to 1
	- save the start timne	*/

int	ft_init_data(t_args *args, t_data *data, int argc, char **argv)
{
	args->philo_number = ft_atoi(argv[1]);
    args->death_time = ft_atoi(argv[2]);
    args->eat_time = ft_atoi(argv[3]);
    args->sleep_time = ft_atoi(argv[4]);
    args->meals = -1;
	if (argc == 6)
        args->meals = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(t_philo) * (args->philo_number));
	if (!data->philo)
		return (EXIT_FAILURE);
	data->philosopher = malloc(sizeof(pthread_t) * (args->philo_number));
	if (!data->philosopher)
		return (ft_mem_free(data), EXIT_FAILURE);
	data->forks = malloc(sizeof(pthread_mutex_t) * (args->philo_number));
	if (!data->forks)
		return (ft_mem_free(data), EXIT_FAILURE);
	data->defender = malloc(sizeof(pthread_mutex_t) * (args->philo_number));
	if (!data->defender)
		return (ft_mem_free(data), EXIT_FAILURE);
	data->print_lock = malloc(sizeof(pthread_mutex_t) * 1);
	if (!data->print_lock)
		return (ft_mem_free(data), EXIT_FAILURE);
	data->stop = 0;
	data->start_time = ft_time();
	return (EXIT_SUCCESS);
}

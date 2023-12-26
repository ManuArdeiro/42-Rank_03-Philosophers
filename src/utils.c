/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolopez- <jolopez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:01:02 by jolopez-          #+#    #+#             */
/*   Updated: 2023/12/19 21:39:49 by jolopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* This function returns the time of the day in miliseconds, both seconds
	and microseconds.	*/

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*	This function waits (sleeps) the quantity of time passed
	as argument, checking every 500 microseconds (0.5ms).	*/
	
void	ft_wait(int time)
{
	long long	start_time;
	long long	current_time;

	start_time = ft_time();
	current_time = start_time;
	while (start_time >= (current_time - time))
	{
		current_time = ft_time();
		usleep(500);
	}
}

/*	This funcion checks if philosopher i is dead:
		If so, prints a message, then blocks the print_lock so nobody is
		able to print and sets the stop status to 0 (it means no more
		messages will be printed). Then unblocks the print_lock. Finally
		it unblocks the left_fork mutex of the philosopher and returns
		failure to stop the loop.	
	Then it checks if meals were reached and the philosopher has not eaten
	before:
		If so, the already_eaten flag is set to 1 and the number of 
		philosophers who has eaten is increased	by 1. When all the 
		philosophers has eaten then the print_lock mutex is	blocked, the
		stop status is updated, the print_lock mutex is unblocked again 
		and failure is returned to stop the loop.	*/

int	ft_check_stop(t_args *args, t_data *data, const int i)
{
	data->time = ft_time() - data->philo->start_time;
	if (data->time - data->philo[i].last_food > data->philo[i].args->death_time)
	{
		printf("%lldms Philosopher %d has died. \n", data->time,
			data->philo[i].id);
		pthread_mutex_lock(data->print_lock);
		data->stop = 1;
		pthread_mutex_unlock(data->print_lock);
		pthread_mutex_unlock(data->philo[i].left_fork);
		return (EXIT_FAILURE);
	}
	if (data->philo[i].foods == data->philo[i].args->meals
		&& data->philo[i].alredy_eaten == 0)
	{
		data->philo[i].alredy_eaten = 1;
		if (++data->philos_eaten == args->philo_number)
		{
			pthread_mutex_lock(data->print_lock);
			data->stop = 1;
			pthread_mutex_unlock(data->print_lock);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/*	This function, with the print_lock mutex blocked (if it previously blocked
	it is not accesible), prints the message:
	- the time from the start
	- the philosopher id
	- a string passed as argument
	if the stop status is set to 0. It means it is not posible to print if
	stop flag is true (because some philosopher is dead).	*/

void	ft_print(t_philo *philo, char *msg)
{
	long long	time;

	time = ft_time() - philo->start_time;
	pthread_mutex_lock(philo->print_lock);
	if (*(philo->stop) == 0)
		printf("%lldms philo %d %s", time, philo->id, msg);
	pthread_mutex_unlock(philo->print_lock);
	return ;
}

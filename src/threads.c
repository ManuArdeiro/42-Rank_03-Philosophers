/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ardeiro <Ardeiro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:11:48 by jolopez-          #+#    #+#             */
/*   Updated: 2023/12/19 01:57:36 by Ardeiro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*	This function creates the threads, one for philosopher. The first thing to
	do is block the print_lock, so nobody will be able to print until all the 
	philosophers will be created.
	Then for every philosopher the data is set and the thread is created,
	calling the routine function.
	Finally, when all the threads were created, the print_lock is unblocked. */

int	ft_create_threads(t_args *args, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->print_lock);
	while (i < args->philo_number)
	{
		if (ft_set_philo(args, data, i))
			return (EXIT_FAILURE);
		pthread_create(&(data->philosopher[i]), NULL, routine,
			&(data->philo[i]));
		i++;
	}
	pthread_mutex_unlock(data->print_lock);
	return (EXIT_SUCCESS);
}

/*	This function deletes the threads. It means all of them. First at all it
	unblocks the defender and waits until the thread finishes for every
	philosopher.
	Then it destrois the mutex for every defender, fork and print_lock.	*/

void	ft_delete_threads(t_args *args, t_data *data)
{
	int	i;

	i = 0;
	while (i < args->philo_number)
	{
		pthread_join(data->philosopher[i], NULL);
		pthread_mutex_unlock(data->philo[i].defender);
		i++;
	}
	i = 0;
	while (i < args->philo_number)
	{
		pthread_mutex_destroy(&(data->defender[i]));
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(data->print_lock[i]));
		i++;
	}
}

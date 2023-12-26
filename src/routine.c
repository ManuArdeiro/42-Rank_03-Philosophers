/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ardeiro <Ardeiro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:48:06 by Ardeiro           #+#    #+#             */
/*   Updated: 2023/12/20 01:53:36 by Ardeiro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*	Action for philosophers:
	- Takes the left then the right forks.
	- Blocks the defender to avoid starting eating while deaths and meals are
	  being checked).
	- Eats and waits the eat_time.
	- 	*/

static void	ft_philo_actions(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken his left fork. \n");
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken his right fork. \n");
	pthread_mutex_lock(philo->defender);
	philo->last_food = ft_time() - philo->start_time;
	ft_print(philo, "is eating. \n");
	if (philo->args->meals != -1)
		philo->foods++;
	pthread_mutex_unlock(philo->defender);
	ft_wait(philo->args->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_print(philo, "is sleeping. \n");
	ft_wait(philo->args->sleep_time);
	ft_print(philo, "is thinking. \n");
	return ;
}

/*	The routine funcion is the functions passed to every thread (philosopher).
	First thing to do is to block the print_lock mutex. This way all the other
	philosophers will wait in this point until in the next line the mutex
	gets unblocked. Notice that we can avoid these lines:
		pthread_mutex_lock(philo->print_lock);
		pthread_mutex_unlock(philo->print_lock)
	and the program will work anyway.
	Then if the philosopher is even will sleep some time (usleep function),
	if it is odd it won't. That's because we want only the half of the 
	philosophers can eat, there are not forks for all of them.
	Then while stop flag is 0 every philosopher will execute the actions in
	ft_philo_actions() one by one (because of the print_lock mutex unblocked,
	if that mutex is not unblocked no any other philosopher could make philo
	actions). */

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = philosopher;
	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_unlock(philo->print_lock);
	if ((philo->id % 2) == 0)
		usleep(500);
	pthread_mutex_lock(philo->print_lock);
	while (*(philo->stop) == 0)
	{
		pthread_mutex_unlock(philo->print_lock);
		ft_philo_actions(philo);
		pthread_mutex_lock(philo->print_lock);
	}
	pthread_mutex_unlock(philo->print_lock);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ardeiro <Ardeiro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:22:39 by jolopez-          #+#    #+#             */
/*   Updated: 2023/12/15 18:47:12 by Ardeiro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* Simnple function to free allocated memory.	*/

void	ft_mem_free(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->philosopher)
		free(data->philosopher);
	if (data->forks)
		free(data->forks);
	if (data->defender)
		free(data->defender);
	if (data->print_lock)
		free(data->print_lock);
	return ;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ardeiro <Ardeiro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:53:24 by adrgonza          #+#    #+#             */
/*   Updated: 2023/12/26 23:55:29 by Ardeiro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/*	The loop blocks the defender to avoid every philosopher i can start eating
	before checking if the program has to stop (if one philosopher is dead or
	are the meals were eaten).	*/

static void	ft_loop(t_args *args, t_data *data)
{
	int	i;

	data->philos_eaten = 0;
	while (data->stop == 0)
	{
		i = 0;
		while (i < args->philo_number)
		{
			pthread_mutex_lock(data->philo[i].defender);
			ft_check_stop(args, data, i);
			pthread_mutex_unlock(data->philo[i].defender);
			i++;
		}
	}
}

/*	This function checks if the number or arguments is valid and if they are
	numbers.	*/

static int	ft_args_checker(int argc, char **argv)
{
	int	i;
	int	j;

	j = 1;
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	while (j < argc)
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (EXIT_FAILURE);
			i++;
		}
		j++;
	}
	if (!ft_atoi(argv[1]) || !ft_atoi(argv[2]) || !ft_atoi(argv[3])
		|| !ft_atoi(argv[4]))
		return (EXIT_FAILURE);
	if (argc == 6)
		if (!ft_atoi(argv[5]))
			return (0);
	return (EXIT_SUCCESS);
}

/*	Main function has several porposes:
	- It checks if arguments are valid.
	- It inits the data configuration allocating the needed mem.
	- It creates the i threads for every philosopher.
	  It means every thread starts its routine function.
	- It starts a loop to check continously if the program has to stop 
	  because a philosopher is dead or the quantity of meals was reached.
	- When the loop finishes, it destrois the threads and frees the mem.
	- Finally it returrns exit success.	*/

int	main(int argc, char **argv)
{
	t_args	args;
	t_data	data;

	if (ft_args_checker(argc, argv))
		return (printf("Error.\n"));
	if (ft_init_data(&args, &data, argc, argv))
		return (printf("Mem allocation not possible.\n"));
	if (ft_create_threads(&args, &data))
		return (ft_mem_free(&data), 0);
	ft_loop(&args, &data);
	ft_delete_threads(&args, &data);
	ft_mem_free(&data);
	return (EXIT_SUCCESS);
}

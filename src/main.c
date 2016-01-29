/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkalb <fkalb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 14:16:53 by fkalb             #+#    #+#             */
/*   Updated: 2015/03/07 23:33:03 by fkalb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"

int			expose_hook(t_all *all)
{
	all->indice = mlx_put_image_to_window(all->mlx, all->win, all->img, 0, 0);
	return (1);
}

int			checkerror(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putendl("FDF must be used with one argument.");
		return (0);
	}
	if (!ft_strendwith(av[1], ".fdf") || *av[1] == '.')
	{
		ft_putendl("Invalid file name.");
		return (0);
	}
	return (1);
}

int			getkey(int key, t_all *all)
{
	if (key == 65307)
		exit (0);
	if (key == 32)
		all->active_neg *= -1;
	if (key == 65451 && (all->ratio < 10))
		all->ratio += 0.1;
	if (key == 65453 && (all->ratio > 0.1))
		all->ratio -= 0.1;
	if (key == 65361)
		move(all, 2);
	if (key == 65362)
		move(all, 3);
	if (key == 65363)
		move(all, 0);
	if (key == 65364)
		move(all, 1);
	free(all->img);
	free(all->data);
	all->img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	all->data = mlx_get_data_addr(all->img, &all->bp, &all->sl, &all->end);
	putpoints(all, &(all->start));
	mlx_put_image_to_window(all->mlx, all->win, all->img, 0, 0);
	return (0);
}

static int	init(t_all *all, int fd)
{
	all->ratio = 0.7;
	all->height_rate = 0;
	all->active_neg = -1;
	if (!(all->start = (t_point*)malloc(sizeof(t_point))))
	{
		ft_putendl("Malloc failed.");
		return (-1);
	}
	all->start->next = NULL;
	get_map(fd, &all->start, all);
	close(fd);
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, WIDTH, HEIGHT, "fkalb - fdf");
	all->img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	all->data = mlx_get_data_addr(all->img, &all->bp, &all->sl, &all->end);
	return (1);
}

int			main(int ac, char **av, char **env)
{
	t_all	all;
	int		fd;

	if (!env || !env[0] || !checkerror(ac, av))
		return (0);
	if ((fd = open(av[1], O_RDONLY)) <= 0)
	{
		ft_putendl("Open failed.");
		return (0);
	}
	if (init(&all, fd) == -1)
		return (0);
	putpoints(&all, &all.start);
	mlx_hook(all.win, 2, 3, &getkey, &all);
	mlx_expose_hook(all.win, expose_hook, &all);
	mlx_loop(all.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkalb <fkalb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 13:54:24 by fkalb             #+#    #+#             */
/*   Updated: 2015/03/08 00:37:34 by fkalb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 800
# define HEIGHT 600

# define WHITE 0xF0F8FF
# define GREY 0x767676
# define BROWN 0x512908
# define GREEN 0x376700
# define BLUE 0x0600A7

# include <mlx.h>
# include <fcntl.h>
# include "libft.h"

typedef struct		s_point
{
	int		line;
	int		col;
	int		high;
	double		posx;
	double		posy;
	int		color;
	struct s_point	*next;
	struct s_point	*down;
}			t_point;

typedef struct		s_all
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int		bp;
	int		sl;
	int		end;
	int		indice;
	int		cols;
	int		lines;
	double		ratio;
	double		height_rate;
	short int	active_neg;
	t_point		*start;
}			t_all;

void			drawtoimage(t_all *all, int x, int y, int color);
void			putpixright(t_all *all, t_point *elem);
void			putpixdown(t_all *all, t_point *elem);
void			isoposition(t_all *all, t_point *elem, double x, double y);
void			putpoints(t_all *all, t_point **start);
void			add_elem(t_point **start, int col, int line, char *s);
void			setdown(t_point **start);
void			get_map(int fd, t_point **start, t_all *all);
void			move(t_all *all, short int dir);

#endif

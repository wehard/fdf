/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:06:16 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 16:59:37 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static int	col_x(int i, t_vertex p0, t_vertex p1)
{
	float	t;
	t_rgba	rgb;
	int		c;

	t = ft_inverse_lerp(i, p0.pos.x, p1.pos.x);
	rgb = ft_lerp_rgba(p0.col, p1.col, t);
	c = ft_get_color(rgb);
	return (c);
}

static int	col_y(int i, t_vertex p0, t_vertex p1)
{
	float	t;
	t_rgba	rgb;
	int		c;

	t = ft_inverse_lerp(i, p0.pos.y, p1.pos.y);
	rgb = ft_lerp_rgba(p0.col, p1.col, t);
	c = ft_get_color(rgb);
	return (c);
}

static void	draw_l(t_frame_buffer *fb, t_vertex p0, t_vertex p1)
{
	t_intvec2	p;
	t_intvec2	d;
	int			yi;
	int			delta;

	d = set_intvec2(p1.pos.x - p0.pos.x, p1.pos.y - p0.pos.y);
	yi = 1;
	if (d.y < 0)
	{
		yi = -1;
		d.y = -d.y;
	}
	delta = 2 * d.y - d.x;
	p = set_intvec2(p0.pos.x, p0.pos.y);
	while (p.x < p1.pos.x)
	{
		frame_buffer_set(fb, p.x, p.y, col_x(p.x, p0, p1));
		if (delta > 0)
		{
			p.y = p.y + yi;
			delta = delta - (2 * d.x);
		}
		delta = delta + (2 * d.y);
		p.x++;
	}
}

static void	draw_h(t_frame_buffer *fb, t_vertex p0, t_vertex p1)
{
	t_intvec2	p;
	t_intvec2	d;
	int			xi;
	int			delta;

	d = set_intvec2(p1.pos.x - p0.pos.x, p1.pos.y - p0.pos.y);
	xi = 1;
	if (d.x < 0)
	{
		xi = -1;
		d.x = -d.x;
	}
	delta = 2 * d.x - d.y;
	p = set_intvec2(p0.pos.x, p0.pos.y);
	while (p.y < p1.pos.y)
	{
		frame_buffer_set(fb, p.x, p.y, col_y(p.y, p0, p1));
		if (delta > 0)
		{
			p.x = p.x + xi;
			delta = delta - (2 * d.y);
		}
		delta = delta + (2 * d.x);
		p.y++;
	}
}

void		draw_line(t_frame_buffer *fb, t_vertex p0, t_vertex p1)
{
	if (ft_abs(p1.pos.y - p0.pos.y) < ft_abs(p1.pos.x - p0.pos.x))
	{
		if (p0.pos.x > p1.pos.x)
			draw_l(fb, p1, p0);
		else
			draw_l(fb, p0, p1);
	}
	else
	{
		if (p0.pos.y > p1.pos.y)
			draw_h(fb, p1, p0);
		else
			draw_h(fb, p0, p1);
	}
}

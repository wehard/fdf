/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:06:16 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/07 22:07:36 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_low(t_frame_buffer *fb, t_depth_buffer *db, t_vertex p0, t_vertex p1)
{
	t_intvec2 p;
	int dx;
	int dy;
	int yi;
	int d;

	float dz = p1.pos.z - p0.pos.z;
	float cz = dz = p0.pos.z;

	dx = p1.pos.x - p0.pos.x;
	dy = p1.pos.y - p0.pos.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy - dx;
	p.y = p0.pos.y;
	p.x = p0.pos.x;
	while (p.x < p1.pos.x)
	{
		cz += dz / dx;
		if (cz < depth_buffer_sample(db, p.x, p.y))
		{
			float t = ft_convert_range(p.x, p0.pos.x, p1.pos.x, 0.0f, 1.0f);
			int c = ft_get_color(ft_lerp_rgba(p0.col, p1.col, t));
			frame_buffer_set(fb, p.x, p.y, c);
			depth_buffer_set(db, p.x, p.y, cz);
		}

		if (d > 0)
		{
			p.y = p.y + yi;
			d = d - (2 * dx);
		}
		d = d + (2 * dy);
		p.x++;
	}
}

static void	draw_line_high(t_frame_buffer *fb, t_depth_buffer *db, t_vertex p0, t_vertex p1)
{
	t_intvec2 p;
	int dx;
	int dy;
	int xi;
	int d;

	float dz = p1.pos.z - p0.pos.z;
	float cz = dz = p0.pos.z;

	dx = p1.pos.x - p0.pos.x;
	dy = p1.pos.y - p0.pos.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = 2 * dx - dy;
	p.x = p0.pos.x;
	p.y = p0.pos.y;
	while (p.y < p1.pos.y)
	{
		cz += dz / dy;
		if (cz < depth_buffer_sample(db, p.x, p.y))
		{
			float t = ft_convert_range(p.y, p0.pos.y, p1.pos.y, 0.0f, 1.0f);
			int c = ft_get_color(ft_lerp_rgba(p0.col, p1.col, t));
			frame_buffer_set(fb, p.x, p.y, c);
			depth_buffer_set(db, p.x, p.y, cz);
		}
		if (d > 0)
		{
			p.x = p.x + xi;
			d = d - (2 * dy);
		}
		d = d + (2 * dx);
		p.y++;
	}
}

void	draw_line(t_frame_buffer *fb, t_depth_buffer *db, t_vertex p0, t_vertex p1)
{
	if (abs((int)p1.pos.y - (int)p0.pos.y) < abs((int)p1.pos.x - (int)p0.pos.x)) /// remove this forbidden function!!
	{
		if (p0.pos.x > p1.pos.x)
			draw_line_low(fb, db, p1, p0);
		else
			draw_line_low(fb, db, p0, p1);
	}
	else
	{
		if (p0.pos.y > p1.pos.y)
			draw_line_high(fb, db, p1, p0);
		else
			draw_line_high(fb, db, p0, p1);
	}
}


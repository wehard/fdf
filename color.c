/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:03:59 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/05 16:00:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

// NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin

float	ft_convert_range(float oldvalue, float oldmin, float oldmax, float newmin, float newmax)
{
	if (oldmin == oldmax)
		return (newmin);
	if (oldvalue == oldmin)
		return (newmin);
	if (oldvalue == oldmax)
		return (newmax);
	return ((((oldvalue - oldmin) * (newmax - newmin)) / (oldmax - oldmin)) + newmin);
}

float	ft_lerp_f(float n1, float n2, float t)
{
	return (n1 + (n2 - n1) * t);
}

t_rgba ft_make_rgba(float r, float g, float b, float a)
{
	t_rgba color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

t_rgba	ft_lerp_rgba(t_rgba c1, t_rgba c2, float t)
{
	t_rgba color;

	color.r = ft_lerp_f(c1.r, c2.r, t);
	color.g = ft_lerp_f(c1.g, c2.g, t);
	color.b = ft_lerp_f(c1.b, c2.b, t);
	color.a = ft_lerp_f(c1.a, c2.a, t);
	return (color);
}

int		ft_get_color(t_rgba c)
{
	int r = (int)(c.r * 255.0f) << 16;
	int g = (int)(c.g * 255.0f) << 8;
	int b = (int)(c.b * 255.0f);
	//int a = (int)(c.a * 255);
	return (r | g | b );
}

int	ft_color_lerp(int c1, int c2, float t)
{
	return (((float)ft_max(c1, c2) + ((float)ft_max(c1, c2) - (float)ft_min(c1, c2)) * t));
}

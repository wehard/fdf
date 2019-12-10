/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:03:59 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/10 19:09:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

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

t_rgba	ft_make_rgba(float r, float g, float b, float a)
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
	int r;
	int g;
	int b;

	r = (int)(c.r * 255.0f) << 16;
	g = (int)(c.g * 255.0f) << 8;
	b = (int)(c.b * 255.0f);
	return (r | g | b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:18:40 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/10 18:49:52 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	make_vec3_pos(float x, float y, float z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 1.0f;
	return (v);
}

t_vec3	make_vec3_rot(float x, float y, float z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0.0f;
	return (v);
}

t_vec3	multiply_vec3(t_vec3 v, float f)
{
	v.x *= f;
	v.y *= f;
	v.z *= f;
	return (v);
}

t_vec3	add_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

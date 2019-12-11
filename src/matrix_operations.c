/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:40:51 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 17:45:26 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4x4	multiply_matrix(t_mat4x4 a, t_mat4x4 b)
{
	t_mat4x4	c;
	int			x;
	int			y;
	int			i;

	c = init_matrix();
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			i = 0;
			while (i < 4)
			{
				c.m[y][x] += a.m[y][i] * b.m[i][x];
				i++;
			}
			x++;
		}
		y++;
	}
	return (c);
}

t_vec3		multiply_matrix_vec3(t_vec3 in, t_mat4x4 m)
{
	t_vec3	o;
	float	w;

	w = 0.0f;
	o.x = in.x * m.m[0][0] + in.y * m.m[1][0] + in.z * m.m[2][0] + m.m[3][0];
	o.y = in.x * m.m[0][1] + in.y * m.m[1][1] + in.z * m.m[2][1] + m.m[3][1];
	o.z = in.x * m.m[0][2] + in.y * m.m[1][2] + in.z * m.m[2][2] + m.m[3][2];
	w = in.x * m.m[0][3] + in.y * m.m[1][3] + in.z * m.m[2][3] + m.m[3][3];
	if (w != 1.0f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
	return (o);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 17:58:04 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"

t_mat4x4	init_matrix(void)
{
	t_mat4x4	mat;
	int			y;
	int			x;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			mat.m[y][x] = 0.0f;
			x++;
		}
		y++;
	}
	return (mat);
}

t_mat4x4	create_identity_matrix(void)
{
	t_mat4x4	mat;
	int			y;
	int			x;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			mat.m[y][x] = x == y ? 1.0f : 0.0f;
			x++;
		}
		y++;
	}
	return (mat);
}

t_mat4x4	create_trs_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_mat4x4 trs;
	t_mat4x4 s;
	t_mat4x4 r;
	t_mat4x4 t;

	s = create_scaling_matrix(scale);
	r = create_rotation_matrix_xyz(rot);
	t = create_translation_matrix(pos);
	trs = multiply_matrix(s, r);
	trs = multiply_matrix(trs, t);
	return (trs);
}

t_mat4x4	create_view_matrix(t_vec3 pos)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[3][0] = -pos.x;
	mat.m[3][1] = -pos.y;
	mat.m[3][2] = -pos.z;
	return (mat);
}

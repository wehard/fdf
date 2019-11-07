/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/07 21:55:09 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "point.h"
#include "matrix.h"
#include "math.h"

/*
**			zfar
**			znear
**
** [x, y, z] ->
**		(asp)			(fov)
**		(h/w * (1 / tan(theta / 2) * x) / z,
**		((1 / tan(theta / 2) * y) / z,
**		z * (zfar / (zfar - znear)) - ((zfar*znear) / (zfar - znear))
**
**
**		afx / z, fy / z, zq - znearq
*/

t_mat4x4	create_proj_matrix(float znear, float zfar, float fov, float s_width, float s_height)
{
	t_mat4x4 mat_proj;

	float a_ratio = (float)s_height / (float)s_width;
	float fovrad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

	mat_proj.m[0][0] = 0.0f;
	mat_proj.m[1][0] = 0.0f;
	mat_proj.m[2][0] = 0.0f;
	mat_proj.m[3][0] = 0.0f;
	mat_proj.m[0][1] = 0.0f;
	mat_proj.m[1][1] = 0.0f;
	mat_proj.m[2][1] = 0.0f;
	mat_proj.m[3][1] = 0.0f;
	mat_proj.m[0][2] = 0.0f;
	mat_proj.m[1][2] = 0.0f;
	mat_proj.m[2][2] = 0.0f;
	mat_proj.m[3][2] = 0.0f;
	mat_proj.m[0][3] = 0.0f;
	mat_proj.m[1][3] = 0.0f;
	mat_proj.m[2][3] = 0.0f;
	mat_proj.m[3][3] = 0.0f;

	mat_proj.m[0][0] = a_ratio * fovrad;
	mat_proj.m[1][1] = fovrad;
	mat_proj.m[2][2] = zfar / (zfar - znear);
	mat_proj.m[3][2] = (-zfar * znear) / (zfar - znear);
	mat_proj.m[2][3] = 1.0f;
	mat_proj.m[3][3] = 0.0f;

	return (mat_proj);
}

t_vec3		multiply_matrix_vec3(t_vec3 in, t_mat4x4 m)
{
	t_vec3 	out;
	float	w;

	out.x = in.x * m.m[0][0] + in.y * m.m[1][0] + in.z * m.m[2][0] + m.m[3][0];
	out.y = in.x * m.m[0][1] + in.y * m.m[1][1] + in.z * m.m[2][1] + m.m[3][1];
	out.z = in.x * m.m[0][2] + in.y * m.m[1][2] + in.z * m.m[2][2] + m.m[3][2];
	w = in.x * m.m[0][3] + in.y * m.m[1][3] + in.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		out.x /= w;
		out.y /= w;
		out.z /= w;
	}
	return (out);
}

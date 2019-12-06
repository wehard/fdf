/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/06 14:25:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "matrix.h"
#include "math.h"

t_mat4x4	init_matrix(void)
{
	t_mat4x4 mat;
	int y;
	int x;

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
	t_mat4x4 mat;
	int y;
	int x;

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

t_mat4x4	create_rotation_matrix_x(float angle)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = 1.0f;
	mat.m[1][1] = cosf(angle);
	mat.m[1][2] = -sinf(angle);
	mat.m[2][1] = sinf(angle);
	mat.m[2][2] = cosf(angle);
	mat.m[3][3] = 1.0f;
	return (mat);
}

t_mat4x4	create_rotation_matrix_y(float angle)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = cosf(angle);
	mat.m[0][2] = -sinf(angle);
	mat.m[1][1] = 1.0f;
	mat.m[2][0] = sinf(angle);
	mat.m[2][2] = cosf(angle);
	return (mat);
}

t_mat4x4	create_rotation_matrix_z(float angle)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = cosf(angle);
	mat.m[0][1] = -sinf(angle);
	mat.m[1][0] = sinf(angle);
	mat.m[1][1] = cosf(angle);
	return (mat);
}

t_mat4x4	create_rotation_matrix_xyz(t_vec3 deg_angle)
{
	t_mat4x4 mat;

	mat = create_rotation_matrix_y(deg_angle.y * (M_PI / 180.0f));
	mat = multiply_matrix(mat, create_rotation_matrix_x(deg_angle.x * (M_PI / 180.0f)));
	mat = multiply_matrix(mat, create_rotation_matrix_z(deg_angle.z * (M_PI / 180.0f)));
	return (mat);
}

t_mat4x4	create_scaling_matrix(t_vec3 scale)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	return (mat);
}

t_mat4x4	create_translation_matrix(t_vec3 translation)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[3][0] = translation.x; // This has translation in the lowest row instead of last column!! Figure it out!
	mat.m[3][1] = translation.y;
	mat.m[3][2] = translation.z;
	return (mat);
}

t_mat4x4	create_trs_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_mat4x4 trs;
	t_mat4x4 s = create_scaling_matrix(scale);
	t_mat4x4 r = create_rotation_matrix_xyz(rot);
	t_mat4x4 t = create_translation_matrix(pos);

	trs = multiply_matrix(s, r);
	trs = multiply_matrix(trs, t);
	return (trs);
}

t_mat4x4	create_perspective_matrix(float fov, float aspect, float znear, float zfar)
{
	t_mat4x4 mat;

	float tanhalfov = tanf((fov / 2.0f) * M_PI / 180.0f);

	mat.m[0][0] = 1.0f / (tanhalfov * aspect); //(1.0f - tanf(fov / 2.0f)) * aspect;
	mat.m[0][1] = 0.0f;
	mat.m[0][2] = 0.0f;
	mat.m[0][3] = 0.0f;

	mat.m[1][0] = 0.0f;
	mat.m[1][1] = -1.0f / tanhalfov; //1.0f - tanf(fov / 2.0f);
	mat.m[1][2] = 0.0f;
	mat.m[1][3] = 0.0f;

	mat.m[2][0] = 0.0f;
	mat.m[2][1] = 0.0f;
	mat.m[2][2] = (-znear - zfar) / (znear - zfar);  //-((zfar + znear) / (zfar - znear));
	mat.m[2][3] = (2.0f * zfar * znear) / (znear - zfar); // -((2.0f * (zfar * znear)) / (zfar - znear));

	mat.m[3][0] = 0.0f;
	mat.m[3][1] = 0.0f;
	mat.m[3][2] = 1.0f;
	mat.m[3][3] = 0.0f;
	return (mat);
}

t_mat4x4	create_ortho_matrix(float top, float bot, float lft, float rgt, float znear, float zfar)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = 2 / (rgt - lft);
    mat.m[0][1] = 0;
    mat.m[0][2] = 0;
    mat.m[0][3] = 0;

	mat.m[1][0] = 0;
	mat.m[1][1] = 2 / (top - bot);
	mat.m[1][2] = 0;
	mat.m[1][3] = 0;

	mat.m[2][0] = 0;
	mat.m[2][1] = 0;
	mat.m[2][2] = -2 / (zfar - znear);
	mat.m[2][3] = 0;

	mat.m[3][0] = -(rgt + lft) / (rgt - lft);
	mat.m[3][1] = -(top + bot) / (top - bot);
	mat.m[3][2] = -(zfar + znear) / (zfar - znear);
	mat.m[3][3] = 1;
	return (mat);
}

t_mat4x4	create_ortho_matrix_2(float s_w, float s_h, float zfar, float znear)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = 2.0f / s_w;
	mat.m[1][1] = 2.0f / s_h;
	mat.m[2][2] = 1.0f / (zfar - znear);
	mat.m[2][3] = -znear / (zfar - znear);
	return (mat);
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

t_mat4x4	multiply_matrix(t_mat4x4 a, t_mat4x4 b)
{
	t_mat4x4 c;
	int x;
	int y;
	int i;

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
	t_vec3 	out;
	float	w;

	w = 0.0f;
	out.x = in.x * m.m[0][0] + in.y * m.m[1][0] + in.z * m.m[2][0] + m.m[3][0];
	out.y = in.x * m.m[0][1] + in.y * m.m[1][1] + in.z * m.m[2][1] + m.m[3][1];
	out.z = in.x * m.m[0][2] + in.y * m.m[1][2] + in.z * m.m[2][2] + m.m[3][2];
	w = in.x * m.m[0][3] + in.y * m.m[1][3] + in.z * m.m[2][3] + m.m[3][3];

	if (w != 1.0f)
	{
		out.x /= w;
		out.y /= w;
		out.z /= w;
	}
	return (out);
}

t_vec3		multiply_matrix_vec3_2(t_vec3 in, t_mat4x4 m)
{
	t_vec3 	out;

	out.x = (m.m[0][0] * in.x) + (m.m[0][1] * in.y) + (m.m[0][2] * in.z) + (m.m[0][3] * in.w);
	out.y = (m.m[1][0] * in.x) + (m.m[1][1] * in.y) + (m.m[1][2] * in.z) + (m.m[1][3] * in.w);
	out.z = (m.m[2][0] * in.x) + (m.m[2][1] * in.y) + (m.m[2][2] * in.z) + (m.m[2][3] * in.w);
	out.w = (m.m[3][0] * in.x) + (m.m[3][1] * in.y) + (m.m[3][2] * in.z) + (m.m[3][3] * in.w);

	if (in.w != 1.0)
	{
		out.x /= out.w;
		out.y /= out.w;
		out.z /= out.w;
	}

	return (out);
}

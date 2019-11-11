/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/11 16:58:49 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "point.h"
#include "matrix.h"
#include "math.h"

/*
//
    // General form of the Projection Matrix
    //
    // uh = Cot( fov/2 ) == 1/Tan(fov/2)
    // uw / uh = 1/aspect
    //
    //   uw         0       0       0
    //    0        uh       0       0
    //    0         0      f/(f-n)  1
    //    0         0    -fn/(f-n)  0
    //
    // Make result to be identity first

    // check for bad parameters to avoid divide by zero:
    // if found, assert and return an identity matrix.
    if ( fov <= 0 || aspect == 0 )
    {
        Assert( fov > 0 && aspect != 0 );
        return;
    }

    float frustumDepth = farDist - nearDist;
    float oneOverDepth = 1 / frustumDepth;

    result[1][1] = 1 / tan(0.5f * fov);
    result[0][0] = (leftHanded ? 1 : -1 ) * result[1][1] / aspect;
    result[2][2] = farDist * oneOverDepth;
    result[3][2] = (-farDist * nearDist) * oneOverDepth;
    result[2][3] = 1;
    result[3][3] = 0;
*/



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

// [row][col]

/*
**	Identity matrix
**
**	[1 0 0 0]
**	[0 1 0 0]
**	[0 0 1 0]
**	[0 0 0 1]
*/

/*
**	Rotation matrices
**
**	X
**
**	[ 1    0       0    ]
**	[ 0  cos(a) -sin(a) ]
**	[ 0  sin(a)  cos(a) ]
**
**	[ cos(a)  0  sin(a) ]
**	[   0     1      0  ]
**	[-sin(a)  0  cos(a) ]
**
**	[ cos(a) -sin(a)  0 ]
**	[ sin(a)  cos(a)  0 ]
**	[   0       0     1 ]
*/

t_mat4x4	create_identity_matrix(void)
{
	t_mat4x4 mat;

	mat.m[0][0] = 1.0f;
	mat.m[0][1] = 0.0f;
	mat.m[0][2] = 0.0f;
	mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f;
	mat.m[1][1] = 1.0f;
	mat.m[1][2] = 0.0f;
	mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f;
	mat.m[2][1] = 0.0f;
	mat.m[2][2] = 1.0f;
	mat.m[2][3] = 0.0f;
	mat.m[3][0] = 0.0f;
	mat.m[3][1] = 0.0f;
	mat.m[3][2] = 0.0f;
	mat.m[3][3] = 1.0f;
	return (mat);
}

t_mat4x4	init_matrix(void)
{
	t_mat4x4 mat;

	mat.m[0][0] = 0.0f;
	mat.m[0][1] = 0.0f;
	mat.m[0][2] = 0.0f;
	mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f;
	mat.m[1][1] = 0.0f;
	mat.m[1][2] = 0.0f;
	mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f;
	mat.m[2][1] = 0.0f;
	mat.m[2][2] = 0.0f;
	mat.m[2][3] = 0.0f;
	mat.m[3][0] = 0.0f;
	mat.m[3][1] = 0.0f;
	mat.m[3][2] = 0.0f;
	mat.m[3][3] = 0.0f;
	return (mat);
}

t_mat4x4	create_rotation_matrix_x(float angle)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = 1.0f;
	mat.m[1][1] = cosf(angle * 0.5f);
	mat.m[1][2] = -sinf(angle * 0.5f);
	mat.m[2][1] = sinf(angle * 0.5f);
	mat.m[2][2] = cosf(angle * 0.5f);
	mat.m[3][3] = 1.0f;
	return (mat);
}

t_mat4x4	create_rotation_matrix_y(float angle)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = cosf(angle * 0.5f);
	mat.m[0][2] = sinf(angle * 0.5f);
	mat.m[1][1] = 1.0f;
	mat.m[2][0] = -sinf(angle * 0.5f);
	mat.m[2][2] = cosf(angle * 0.5f);
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

t_mat4x4	create_rotation_matrix_xyz(t_vec3 rad_angle)
{
	t_mat4x4 mat;

	mat = multiply_matrix(create_identity_matrix(), create_rotation_matrix_y(rad_angle.y));
	mat = multiply_matrix(mat, create_rotation_matrix_x(rad_angle.x));
	mat = multiply_matrix(mat, create_rotation_matrix_z(rad_angle.z));
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
	mat.m[0][3] = translation.x;
	mat.m[1][3] = translation.y;
	mat.m[2][3] = translation.z;
	return (mat);
}

t_mat4x4	create_proj_matrix(float znear, float zfar, float fov, float s_width, float s_height)
{
	t_mat4x4 mat_proj;

	mat_proj = create_identity_matrix();

	float a_ratio = (float)s_height / (float)s_width;
	float fovrad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f); //  / 180.0f * 3.14159f

	mat_proj.m[0][0] = a_ratio * fovrad;
	mat_proj.m[1][1] = fovrad;
	mat_proj.m[2][2] = zfar / (zfar - znear);
	mat_proj.m[3][2] = (-zfar * znear) / (zfar - znear);
	mat_proj.m[2][3] = 1.0f;
	mat_proj.m[3][3] = 0.0f;

	/* float frustumDepth = zfar - znear;
    float oneOverDepth = 1 / frustumDepth;
	int lefthanded = 1;

    mat_proj.m[1][1] = 1 / tan(0.5f * fov);
    mat_proj.m[0][0] = (lefthanded ? 1 : -1 ) * mat_proj.m[1][1] / a_ratio;
    mat_proj.m[2][2] = zfar * oneOverDepth;
    mat_proj.m[3][2] = (-zfar * znear) * oneOverDepth;
    mat_proj.m[2][3] = 1.0f;
    mat_proj.m[3][3] = 0.0f; */

	return (mat_proj);
}

t_mat4x4	create_trs_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scaale)
{
	t_mat4x4 mat;

	return (mat);
}

t_mat4x4	multiply_matrix(t_mat4x4 a, t_mat4x4 b)
{
	t_mat4x4 res;
	int i;
	int j;
	int k;

	res = init_matrix();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			while (k < 4)
			{
				res.m[i][j] += a.m[i][k] * b.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
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
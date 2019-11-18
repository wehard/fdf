/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/18 17:43:50 by wkorande         ###   ########.fr       */
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
**	[ 1    0       0    ] [x]
**	[ 0  cos(a) -sin(a) ] [y]
**	[ 0  sin(a)  cos(a) ] [z]
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
	mat.m[0][2] = sinf(angle);
	mat.m[1][1] = 1.0f;
	mat.m[2][0] = -sinf(angle);
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
	mat.m[3][0] = translation.x;
	mat.m[3][1] = translation.y;
	mat.m[3][2] = translation.z;
	return (mat);
}

// void setProjectionMatrix(const float &angleOfView, const float &near, const float &far, Matrix44f &M)
// {
//     // set the basic projection matrix
//     float scale = 1 / tan(angleOfView * 0.5 * M_PI / 180);
//     M[0][0] = scale; // scale the x coordinates of the projected point
//     M[1][1] = scale; // scale the y coordinates of the projected point
//     M[2][2] = -far / (far - near); // used to remap z to [0,1]
//     M[3][2] = -far * near / (far - near); // used to remap z [0,1]
//     M[2][3] = -1; // set w = -z
//     M[3][3] = 0;
// }

// void multPointMatrix(const Vec3f &in, Vec3f &out, const Matrix44f &M)
// {
//     //out = in * M;
//     out.x   = in.x * M[0][0] + in.y * M[1][0] + in.z * M[2][0] + /* in.z = 1 */ M[3][0];
//     out.y   = in.x * M[0][1] + in.y * M[1][1] + in.z * M[2][1] + /* in.z = 1 */ M[3][1];
//     out.z   = in.x * M[0][2] + in.y * M[1][2] + in.z * M[2][2] + /* in.z = 1 */ M[3][2];
//     float w = in.x * M[0][3] + in.y * M[1][3] + in.z * M[2][3] + /* in.z = 1 */ M[3][3];

//     // normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
//     if (w != 1) {
//         out.x /= w;
//         out.y /= w;
//         out.z /= w;
//     }
// }

t_mat4x4	create_proj_matrix(float znear, float zfar, float fov, float aspect)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = 1.0f / (tan(fov / 2.0f) * aspect); //(1.0f - tanf(fov / 2.0f)) * aspect;
	mat.m[1][1] = 1.0f / tan(fov / 2.0f); //1.0f - tanf(fov / 2.0f);
	mat.m[2][2] = (-znear - zfar) / (znear - zfar);  //-((zfar + znear) / (zfar - znear));
	mat.m[2][3] = -((2.0f * znear * zfar) / (znear - zfar)); // -((2.0f * (zfar * znear)) / (zfar - znear));
	mat.m[3][2] = 1.0f;
	mat.m[3][3] = 0.0f;
	return (mat);
}

t_mat4x4	create_ortho_matrix(float top, float bot, float lft, float rgt, float zfar, float znear)
{
	t_mat4x4 mat;

	mat = create_identity_matrix();
	mat.m[0][0] = 2.0f / (rgt - lft); //1.0f / (rgt - lft); // 1.0 over width
	mat.m[1][1] = 2.0f / (bot - top); //1.0f / (bot - top);
	mat.m[2][2] = 2.0f / (znear - zfar); //-(2.0f / (zfar - znear));
	mat.m[2][3] = (zfar + znear) / (zfar - znear); //((zfar + znear) / (zfar - znear));

	//mat.m[0][3] =  (lft + rgt) / (lft -  rgt);
	//mat.m[1][3] =  (bot + top) / (bot -  top);
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

// note that we read the multiplication from right to left
// gl_Position = projection * view * model * vec4(aPos, 1.0);

/*
** A model matrix transforms a point from its local space into world space coordinates
** It also applies rotation and scale to the point.
** Scaling is performed first, then rotation and lastly, translation.
*/

t_mat4x4	create_model_matrix()
{
	t_mat4x4 mat;

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


t_vec3		multiply_matrix_vec3_test(t_vec3 in, t_mat4x4 m)
{
	t_vec3 	out;

	out.x = (m.m[0][0] * in.x) + (m.m[0][1] * in.y) + (m.m[0][2] * in.z) + (m.m[0][3] * in.w);
	out.y = (m.m[1][0] * in.x) + (m.m[1][1] * in.y) + (m.m[1][2] * in.z) + (m.m[1][3] * in.w);
	out.z = (m.m[2][0] * in.x) + (m.m[2][1] * in.y) + (m.m[2][2] * in.z) + (m.m[2][3] * in.w);
	out.w = (m.m[0][3] * in.x) + (m.m[1][3] * in.y) + (m.m[2][3] * in.z) + (m.m[3][3] * in.w);

	if (in.w == 1.0f)
	{
		out.x /= out.w;
		out.y /= out.w;
		out.z /= out.w;
	}
	return (out);
}

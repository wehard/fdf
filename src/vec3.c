/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:18:40 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/06 14:30:01 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	make_vec3_pos(float x, float y, float z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w	= 1.0f;
	return (v);
}

t_vec3	make_vec3_rot(float x, float y, float z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w	= 0.0f;
	return (v);
}

/*
**	Transforms point to world space. Applies rotation and scale.
*/

t_vec3		transform_point(t_vec3 v, t_vec3 translate, t_vec3 rot, t_vec3 scale)
{
	// glm::mat4 myModelMatrix = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
	// glm::vec4 myTransformedVector = myModelMatrix * myOriginalVector;
	//v = multiply_matrix_vec3(v, create_rotation_matrix_xyz(rot));
	v = multiply_matrix_vec3(v, create_translation_matrix(translate));
	v = multiply_matrix_vec3(v, create_scaling_matrix(scale));
	return (v);
}

t_vec3		translate_point_3d(t_vec3 p, t_vec3 translation)
{
	t_vec3 v;

	v.x += translation.x;
	v.y += translation.y;
	v.z += translation.z;
	return (v);
}

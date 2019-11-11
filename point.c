/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:14:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/11 18:18:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"
#include "matrix.h"

t_vec2	make_vec2(float x, float y)
{
	t_vec2 v;

	v.x = 0;
	v.y = 0;
	return (v);
}

t_vec3	make_vec3(float x, float y, float z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
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

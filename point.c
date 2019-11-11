/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:14:13 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/07 17:18:50 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

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
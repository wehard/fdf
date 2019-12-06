/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 13:40:47 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/06 14:28:49 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vertex	make_vertex(float x, float y, float z, t_rgba c)
{
	t_vertex v;

	v.pos = make_vec3_pos(x, y, z);
	v.col = c;
	return (v);
}

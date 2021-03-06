/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:21:07 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/12 16:31:31 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec2		make_vec2(float x, float y)
{
	t_vec2 v;

	v.x = x;
	v.y = y;
	return (v);
}

t_intvec2	make_intvec2(int x, int y)
{
	t_intvec2 v;

	v.x = x;
	v.y = y;
	return (v);
}

t_intvec2	set_intvec2(int x, int y)
{
	t_intvec2 v;

	v.x = x;
	v.y = y;
	return (v);
}

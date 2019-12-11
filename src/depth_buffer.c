/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 13:02:05 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/11 17:14:54 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void			depth_buffer_set(t_depth_buffer *db, int x, int y, float f)
{
	if (x < 0 || x >= db->width || y < 0 || y >= db->height)
		return ;
	db->data[y * db->width + x] = f;
}

t_depth_buffer	*create_depth_buffer(int width, int height)
{
	t_depth_buffer *db;

	if (!(db = (t_depth_buffer*)malloc(sizeof(t_depth_buffer))))
	{
		throw_error("error: create depth buffer failed!");
		return (NULL);
	}
	db->width = width;
	db->height = height;
	if (!(db->data = (float*)malloc(sizeof(float) * (db->width * db->height))))
	{
		throw_error("error: create depth buffer data failed!");
		return (NULL);
	}
	return (db);
}

void			clear_depth_buffer(t_depth_buffer *db, float value)
{
	int size;
	int i;

	size = db->width * db->height;
	while (i < size)
	{
		db->data[i] = value;
		i++;
	}
}

float			depth_buffer_sample(t_depth_buffer *db, int x, int y)
{
	if (x < 0 || x >= db->width || y < 0 || y >= db->height)
		return (0.0f);
	return (db->data[y * db->width + x]);
}

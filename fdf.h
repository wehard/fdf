/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:23:29 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/08 15:00:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "matrix.h"
# include "point.h"

# define WIN_W 1280
# define WIN_H 720

# define ESC 53

typedef struct 		s_line
{
	t_vec3			p0;
	t_vec3			p1;
	int				color;
}					t_line;

typedef struct		s_mouse_data
{
	int				x;
	int				y;
	int				oldx;
	int				oldy;
}					t_mouse_data;

typedef struct		s_v_map
{
	t_vec3			*v;
	int				w;
	int				h;
}					t_v_map;

typedef struct		s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_mat4x4		*m_proj;
	t_v_map			*v_map;
	t_mouse_data 	*mouse_data;
	float			delta_time;
}					t_mlx_data;

t_vec3	make_vec3(float x, float y, float z);

#endif

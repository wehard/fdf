/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:23:29 by wkorande          #+#    #+#             */
/*   Updated: 2019/11/13 16:42:49 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "matrix.h"
# include "point.h"

# define GREEN 0x00FF00
# define RED 0xFF0000
# define WHITE 0xFFFFFF

# define WIN_W 720
# define WIN_H 720

# define ESC 53
# define SPACE 49
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_R 15
# define KEY_F 3
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20


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
	int				dx;
	int				dy;
}					t_mouse_data;

typedef struct		s_v_map
{
	t_vec3			*v;
	t_vec3			pos;
	t_vec3			rot;
	t_vec3			scale;
	int				size;
	int				w;
	int				h;
}					t_v_map;

typedef struct		s_frame_buffer
{
	void			*img;
	char			*d_addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				w;
	int				h;
}					t_frame_buffer;

typedef struct		s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_frame_buffer	*f_buf;
	t_mat4x4		*m_proj;
	t_mat4x4		perspective_matrix;
	t_mat4x4		ortho_matrix;
	t_v_map			*v_map;
	t_mouse_data 	*mouse_data;
	float			delta_time;
}					t_mlx_data;

void			frame_buffer_set(t_frame_buffer *fb, int x, int y, int color);
void			clear_frame_buffer(t_frame_buffer *fb);
t_frame_buffer	*create_frame_buffer(t_mlx_data *mlx_data);

void			draw_line(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1);
void			draw_line_simple(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1);
void			draw_tri(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1, t_vec3 p2);
void			draw_quad(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1, t_vec3 p2, t_vec3 p3);

int				read_map_data(int fd, t_v_map **map);
t_v_map			*create_v_map(int w, int h);
int				throw_error(char *e);

int				on_key_down(int key, void *param);
int				mouse_event(int button, int x, int y, void *param);

#endif

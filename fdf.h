/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:23:29 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/02 16:53:37 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "matrix.h"
# include "point.h"

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF

# define WIN_W 1280
# define WIN_H 720

# define ESC   53  //0xff1b 53
# define SPACE 49  //0x0020 49
# define KEY_W 13  //0x0077 13
# define KEY_A 0   //0x0061 0
# define KEY_S 1   //0x0073 1
# define KEY_D 2   //0x0064 2
# define KEY_Q 12  //0x0071 12
# define KEY_E 14  //0x0065 14
# define KEY_R 15  //0x0072 15
# define KEY_F 3   //0x0066 3
# define KEY_1 18  //0x0030 18
# define KEY_2 19  //0x0031 19
# define KEY_3 20  //0x0033 20
# define KEY_Z 6
# define KEY_X 7

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124


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

typedef struct		s_camera
{
	t_vec3			pos;
	t_mat4x4		v_matrix;
}					t_camera;


typedef struct		s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_frame_buffer	*f_buf;
	t_mat4x4		*m_proj;
	t_mat4x4		perspective_matrix;
	t_mat4x4		ortho_matrix;
	t_camera		camera;
	t_v_map			*v_map;
	t_mouse_data 	mouse_data;
	float			delta_time;
}					t_mlx_data;

void			frame_buffer_set(t_frame_buffer *fb, int x, int y, int color);
void			clear_frame_buffer(t_frame_buffer *fb);
t_frame_buffer	*create_frame_buffer(t_mlx_data *mlx_data);

void			draw_line(t_frame_buffer *fb, t_intvec2 p0, t_intvec2 p1, int color);
void			draw_line_simple(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1);
void			draw_tri(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1, t_vec3 p2);
void			draw_quad(t_frame_buffer *fb, t_vec3 p0, t_vec3 p1, t_vec3 p2, t_vec3 p3);

int				read_map_data(int fd, t_v_map **map);
t_v_map			*create_v_map(int w, int h);
int				throw_error(char *e);

int				on_key_down(int key, void *param);
int				mouse_event(int button, int x, int y, void *param);

void			ft_print_matrix(t_mat4x4 m, int precision);
void			ft_print_vec3(t_vec3 v, int precision);

#endif

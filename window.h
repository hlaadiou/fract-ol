/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:53:02 by hlaadiou          #+#    #+#             */
/*   Updated: 2023/05/04 12:04:17 by hlaadiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# define ESC 53   // key escape
# define ENTER 36 // key "enter"
# define FOLLOW 3 // key "f"
# define COLOR 8  // key "c"
# define UP 126   // key "arrow up"
# define DOWN 125 // key "arrow down"
# define PENGUIN 35 // key "p"
# define RAND_COLOR 15 // key "r"

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;

}	t_win;

typedef struct s_img
{
	t_win	win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_square
{
	unsigned short int	x;
	unsigned short int	y;
	unsigned short int	size;
	int					color;
}	t_square;

t_win	new_program(int w, int h, char *str);
t_img	new_image(int w, int h, t_win window);
int		read_keys(int key_pressed, void *param);
int 	read_mouse(int button, int mouse_x, int mouse_y, void *param);

#endif

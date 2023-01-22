/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:58:35 by gsever            #+#    #+#             */
/*   Updated: 2023/01/23 01:41:42 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h> /* OK:
	write()		-> System call used to write data from the buffer
		ssize_t	write(int fd, const void *buf, size_t count);
https://man7.org/linux/man-pages/man2/write.2.html
	read()		-> Read from a file descriptor
		ssize_t read(int fd, void *buf, size_t count);
https://man7.org/linux/man-pages/man2/read.2.html
*/
# include <stdlib.h> /* OK:
	free()		-> Deallocatig all allocated memory
		void free(void *ptr);
https://www.ibm.com/docs/en/i/7.5?topic=functions-free-release-storage-blocks
	exit()		-> Closing everything with atexit() and terminates program
		noreturn void exit(int status);
https://man7.org/linux/man-pages/man3/exit.3.html
*/
# include <stdio.h> /* OK:
	printf()	-> A library function to send formatted output to the screen
		int printf(const char *restrict format, ...);
https://man7.org/linux/man-pages/man3/printf.3.html
	perror()	-> System error messages
		void perror(const char *string);
https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-perror\
-print-error-message
*/
# include <stdint.h> /* OK: -NUMBERS-
	Type	 	Name		Num_Bytes	Num_Bits	Integer_Range
	int8_t	 ->	char			1			8		-128 to 127,
	int16_t	 ->	short			2			16		-32768 to 32767,
	int32_t	 ->	int				4			32		-2147483648 to 2147483647,
	int64_t	 ->	long long		8			64	-9.223372e+18 to 9.223372e+18
	uint8_t	 ->	unsigned char	1			8			0 to 255,
	uint16_t ->	unsigned short	2			16			0 to 65535,
	uint32_t ->	unsigned int	4			32			0 to 4294967295,
	uint64_t ->	unsigned l_l 	8			64		0 to 18446744073709551615
*/
# include <string.h> /* OK:
	malloc()	-> Allocating memory with NULL
		void *malloc(size_t size);
https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-malloc-\
reserve-storage-block
	strerror()	-> System error messages; Writing int errno's string value.
		char *strerror(int errnum);
https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-strerror-\
get-pointer-runtime-error-message
*/
# include <fcntl.h> /*  OK: -File control-
	open()		-> Open or Create a file for reading or writing.
		int open(const char *path, int oflag, . . .);
https://www.ibm.com/docs/en/i/7.5?topic=ssw_ibm_i_75/apis/open.htm
	close()		-> Close File or Socket descriptor.
		int close(int fd);
https://www.ibm.com/docs/en/i/7.5?topic=ssw_ibm_i_75/apis/close.htm
*/
# include <errno.h> /* OK: int errno = 0;
	errno;
*/
# include "../libraries/libft/includes/libft.h"
# include "../libraries/minilibx_linux/mlx.h"
# include "../libraries/minilibx_opengl/mlx.h"
# include "key_hooks.h" /* Keyboard/Mouse Press */
# include "map_errors.h"
# include "colors.h" /* 🟥 🟩 🟦
	BLACK	"\033[0;30m"	B_RED		"\033[1;31m"
	RED		"\033[0;31m"	B_GREEN		"\033[1;32m"
	GREEN	"\033[0;32m"	B_YELLOW	"\033[1;33m"
	YELLOW	"\033[0;33m"	B_BLUE		"\033[1;34m"
	BLUE	"\033[0;34m"	B_CYAN		"\033[1;36m"
	PURPLE	"\033[0;35m"	B_RESET		"\033[1m"
	CYAN	"\033[0;36m"
	WHITE	"\033[0;37m"
	END		"\033[m"
	RESET	"\033[0m"
*/

# include <stdbool.h>
# include <math.h>


# define CMD_CLEAR	"\e[1;1H\e[2J"

// Usually if have problem any func()s, returning ERROR=-1
# define ERROR					-1
# define PROMPT					"cub3D"

# define WINDOW_W				800//800
# define WINDOW_H				600//800

# define WHITESPACES			" \t\n\r"

/* ---------------MAP CONTROL DEFINES---------------- */
// " " -> Empty, 1 -> Wall, 0 -> Ground, M -> Sprite, Z -> second sprite
# define MAP_ARGUMENTS			" 10NSEW\r\nMZCO"
# define MAP_CHARS				" 10NSEWMZCO"
# define MAP_W_OUT_ONE			"0NSEWMZCO"
# define MAP_PLY_CANT_GO			"1MZC"
# define MAP_RAY_CAN_GO			"0NSEWMZO"
# define HIT					1
// # define WALL					1
/*
			N -> North Angle
	W -> West Angle		E -> East Angle
			S -> South Angle
*/
# define MAP_CHARACTER_ANGLE	"NSEW"
# define MAP_ANGLE				"NOSOEAWE"
# define MAP_COVERING			"FC"
// \r -> Carriage Return, \n -> New Line
# define MAP_WHITESPACES		" \r\n"
# define RGB_CHR				"0123456789,"
/* -------------------------------------------------- */

/* -----------------MINIMAP DEFINES------------------ */
# define SCREEN_RATE			2
# define MINIMAP_RATE_W			(WINDOW_W / SCREEN_RATE)
# define MINIMAP_RATE_H			(WINDOW_H / SCREEN_RATE)
# define BOX_SIZE				16
/* -------------------------------------------------- */

/* ------------------PLAYER DEFINES------------------ */
// 1º = 0.0174532925 radian
# define ONE_DEGREE					(M_PI / 180.0)// FOV
// 1 rad = 57.2957795131 degree
# define ONE_RADIAN					(180.0 / M_PI)
/*
		π = 180º	</>	1 rad = 180 / π

	66º = 11π / 30			-> 1980 / 30 = 66
	66º = 11 * M_PI / 30	-> 1980 / 30 = 66
	66º = 66 * (M_PI / 180.0)
	66º = 1.15191730631626 radians
*/
# define PLAYER_ANGLE			(ONE_DEGREE * 66)
# define RAY_COUNT				(PLAYER_ANGLE * 2)
# define PLAYER_THICKNESS		2
# define FOV					60
# define FOV_THICKNESS			(WINDOW_W)
# define PLAYER_ROTATION_SPEED	1.50
# define PLAYER_WALK_SPEED		0.80
/* -------------------------------------------------- */





/* ************************************************************************** */
/* STRUCT DEFINES AREA                                                        */
/* ************************************************************************** */

/**
 * @brief MLX's image's data.
 * 
 * @param ptr* image identifier
 * @param addr* image
 * @param bpp depth of image
 * @param size_line	number of bytes used to store one line of image
 * @param endian little or big endian --> arab and eng keyboard types.
 * 
 * @note Su anlik kullanilan ptr, addr, oluyor. Digerleri suanlik kullanilmio.
 */
typedef struct s_mlximg
{
	void	*ptr;
	int		*addr;// bunu char* yapinca my_mlx_pixel_put() dogru calisiyor cunku 1 byte'ye biz 4 byte veriyoruz falan falan :D
	int		bpp;
	int		line_size;
	int		endian;
}		t_mlximg;

/**
 * @brief Main MLX window's data.
 * 
 * @param img
 * @param minimap
 * @param ptr*
 * @param win*
 * 
 * @note MLX'imizin butun islevi burada basliyor.
 */
typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}		t_mlx;

typedef struct s_ray
{
	double	pos_x;// ray end start_to_end end location
	double	pos_y;// ray starting_to_end end location
	bool	is_hit_x;
	bool	is_hit_y;
	double	hit_x;// ray hit_the_wall location -> dx
	double	hit_y;// ray hit_the_wall location -> dy
	double	distance;// clear ray distance.
	double	original_distance;//kacan isinlari engelleyen.
	double	distance_v;// vertical distance.
	double	distance_h;// horizontal distance;
	bool	hit_h;
	bool	hit_v;
	int		dir_x;
	int		dir_y;
	//*******
	// double	pos_x;// ray end start_to_end end location
	// double	pos_y;// ray starting_to_end end location
	// bool	is_hit_x;
	// bool	is_hit_y;
	// double	hit_x;// ray hit_the_wall location -> dx
	// double	hit_y;// ray hit_the_wall location -> dy
	// double	distance;// clear ray distance.
	// double	original_distance;//kacan isinlari engelleyen.
	// double	distance_v;// vertical distance.
	// double	distance_h;// horizontal distance;
	// bool	hit_h;
	// bool	hit_v;
	// bool	is_wall;
	// int		dir_x;
	// int		dir_y;
	// bool	is_sprite[2];
	// // double	sprite_distance;
	bool	is_door;
	// double	door_open_pos_x;// If ray find opened door ('O') saving location.
	// double	door_open_pos_y;// If ray find opened door ('O') saving location.
	// double	minimap_ray_color;
}		t_ray;

typedef struct s_player
{
	double	pos_x;// start location
	double	pos_y;// start location
	double	dir_x;// initial direction location
	double	dir_y;// initial direction location
	double	plane_x;// 0
	double	plane_y;// 0.66 -> 66º fov look angle
	double	walk_speed;
	double	rotation_angle;
	double	default_rotation_angle;
	double	default_pos_x;
	double	default_pos_y;
	double	last_location_x;
	double	last_location_y;
}		t_player;

typedef struct s_mouse
{
	double	rotation_angle;
	int		screen_mid;
	bool	is_enable;
}		t_mouse;

typedef struct s_key
{
	int		value;
	int		screen_mid;
	bool	door_open_command;
	bool	show_mini_map;
	bool	help_page;
}		t_key;

typedef struct s_map
{
	char	**map;
	char	*l_free;
	int		max_x;
	int		max_y;
}		t_map;

/**
 * @brief Just one xpm file data.
 */
typedef struct	s_xpm
{
	t_mlximg	img;
	int			width;
	int			height;
}		t_xpm;

typedef struct	s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*rgb_f;
	char	*f;
	int		*rgb_c;
	char	*c;
	char	*sprite[2];
	char	*door;
	char	*crosshair;
}		t_texture;

typedef struct s_sprite
{
	bool	is_hit;
	double	s_x;
	double	s_y;
	double	distance;
}		t_sprite;

typedef struct s_main
{
	t_texture	texture;
	t_map		map;//OK
	t_mlx		mlx;//OK
	t_mlximg	screen;
	t_mlximg	mini_map;
	t_xpm		xpm[8];// all xpm files data array.
	// t_xpm		xpm;
	t_key		key;
	t_mouse		mouse;
	t_sprite	sprite;
	t_player	ply;
	t_ray		ray;
}		t_main;


/* ************************************************************************** */
/* FUNCTION PROTOTYPES                                                        */
/* ************************************************************************** */

// check_all.c
int		check_args(int	argc, char	**argv);
int		check_map(t_main *main, char **argv);

// door.c
void	check_door_open_or_close(t_main *main, double x, double y);

//exit.c
void	linux_mlx_free(t_main *main);
int		ft_exit(t_main *main);

// help_page.c
void	draw_information(t_main *main);
void	open_help_page(t_main *main);

// draw_all.c
int		draw_mlx_window(t_main *main);

// draw_minimap.c
void	put_pixel(int x, int y, double color, t_main *main);
void	draw_player_position(t_main *main);
void	draw_minimap(t_main *main);

// draw_pixel.c
void	my_mlx_pixel_put(t_mlximg *img, int x, int y, int color);

// draw_screen.c
void	draw_background( t_main *main);
void	_3D(t_main *main, int ray_count);
void	draw_ray(t_main *main, double angle, int ray_count);
void	raycasting(t_main *main, double angle, int ray_count);

// draw_xpm.c
void	draw_xpm_to_wall(t_main *main, int location, int oran, t_xpm xpm);
void	draw_xpm_to_sprite(t_main *main, int location, int oran, t_xpm xpm);
void	put_xpm_to_sprite(t_main *main, int location, t_xpm xpm);

// error.c
int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);

// hooking.c
int		key_press(int keycode, t_main *main);
int		key_release(int keycode, t_main *main);
int		mouse_move(int x, int y, t_main *main);

// init_all_2.c
void	init_all_xpm_others(t_main *main);
void	init_all_xpm_sprites(t_main *main);
int		init_all_xpm_files(t_main *main);
int		init_mlx_draw(t_main *main);

// init_all.c
int		init_all(t_main *main);

// init_cub3d.c
int		init_cub3d_image(t_main *main);
int		init_cub3d_window(t_main *main);
int		init_cub3d(t_main *main);

// key_button.c
int		key_press(int keycode, t_main *main);
int		key_release(int keycode, t_main *main);

// map_borders.c
int		map_borders_inside(t_main *main);
int		map_borders_left(t_main *main);
int		map_borders_bottom(t_main *main);
int		map_borders_right(t_main *main);
int		map_borders_top(t_main *main);

// map_check_rgb.c
int		map_definitions_rgb_c(t_main *main);
int		map_definitions_rgb_f(t_main *main);
int		map_definitions_rgb(t_main *main);
int		map_definitions_check_rgb(t_main *main);

// map_check.c
int		xpm_file_check(char *str, char *name);
int		map_definitions_check(int count, char *line, int limit, t_main *main);

// map_free.c
void	free_definitions(t_main *main);

// map_read.c
int		map_definitions_invalid_input(char *line, int limit, t_main *main);
void	map_definitions_init(t_main *main);
int		map_definitions(char *line, t_main *main);
char	*map_read(int fd);

// map_to_struct.c
int		map_borders(t_main *main);
int		map_max_lenght(char *line, char c);
int		map_find_borders(char *line, int start, int *map_end);
int		map_skip_empty_line(char *line, int limit);
int		map_map(char *line, int start, t_main *main);

// player_move.c
void	player_turn(t_main *main, int way, double val);
void	player_move(t_main *main, int way, double val);

// player.c
void	update_player_all(t_main *main);
void	set_player_default_pos(t_main *main);
void	init_set_player(t_main *main, int x, int y);

// ray.c
double	ray_vertical(t_main *main, double angle, double dir_x, double dir_y);
double	ray_horizontal(t_main *main, double angle, double dir_x, double dir_y);

// utils_func.c
void	free_pstr(char **line);
char	*ft_chrjoin(char *s1, char c);
int		ft_strncmp_edited(const char *s1, const char *s2, size_t n);
int		ft_strcmp_edited(char *s1, char *s2);

// utils_map.c
char	*map_split_stringfind(const char *s, char c, int max);
size_t	map_split_wordcount(char *s, char c);
char	**map_split(char *line, char c, int max);

// utils_wall.c
int		next_step_is_wall(t_main *main, double x, double y);
int		is_wall(t_main *main, double x, double y, double angle);
int		is_wall_v2(t_main *main, double x, double y);

#endif
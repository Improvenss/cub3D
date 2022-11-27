/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:58:35 by gsever            #+#    #+#             */
/*   Updated: 2022/11/27 07:23:27 by gsever           ###   ########.fr       */
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
# include <limits.h> /* OK:
*/
# include <math.h> /* OK: Allow all math func()s. */
# include "../libraries/libft/includes/libft.h"
# include "../libraries/minilibx_linux/mlx.h"
# include "../libraries/minilibx_opengl/mlx.h"
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
# include "key_hooks.h" /* Keyboard/Mouse Press */

# define CMD_CLEAR	"\e[1;1H\e[2J"

// Usually if have problem any func()s, returning ERROR=-1
# define ERROR		-1
# define PROMPT		"cub3D"

# define WINDOW_W				1100//800
# define WINDOW_H				800//800
# define SCREEN_RATE			2
# define PLAYER_THICKNESS		8
# define PLAYER_WALKSPEED		6
# define PLAYER_ROTATION_SPEED	5
# define FOV					60// 60º Player's eye degree.
# define FOV_THICKNESS			120// RayTracing's ray count.
// # define SIZE					64// When we don't use this minimap being fully square.

// " " -> Empty, 1 -> Wall, 0 -> Ground, 
// N -> North Angle, S -> South Angle, E -> East Angle, W -> West Angle, 
// \r -> Carriage Return, \n -> New Line
# define MAP_ARGUMENTS			" 10NSEW\r\n"
# define MAP_CHARACTER_ANGLE	"NSWE"
# define MAP_ANGLE				"NOSOWEEA"
# define MAP_COVERING			"FC"
# define RGB_CHR				"0123456789,"

# define WHITESPACES			" \t\n"
# define MAP_WHITESPACES		"\r\n"

/* ************************************************************************** */
/* STRUCT DEFINES AREA													  	  */
/* ************************************************************************** */

// typedef struct s_ray {
// 	double mesafe;
// 	double x;
// 	double y;
// }		t_ray;

// typedef struct s_key {
// 	int up;
// 	int down;
// 	int right;
// 	int left;
// }		t_key;

typedef struct s_player {
	double	x;
	double	y;
	int		thickness;
	double	rotationAngle;
	double	walkSpeed;
}		t_player;

/**
 * @brief MLX's image's data.
 * 
 * @param ptr* image identifier
 * @param addr* image
 * @param bits_per_pixel depth of image
 * @param size_line	number of bytes used to store one line of image
 * @param endian little or big endian --> arab and eng keyboard types.
 * 
 * @note Su anlik kullanilan ptr, addr, oluyor. Digerleri suanlik kullanilmio.
 */
typedef struct s_mlximg
{
	void	*ptr;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_mlximg;

/**
 * @brief Main MLX window's data.
 * 
 * @param img
 * @param ptr*
 * @param win*
 * 
 * @note MLX'imizin butun islevi burada basliyor.
 */
typedef struct s_mlx
{
	t_mlximg	img;
	void		*ptr;
	void		*win;
}		t_mlx;


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
}		t_texture;

typedef struct s_main
{
	// t_ray		ray;
	// t_key		key;
	t_player	ply;
	t_texture	texture;
	t_mlx		*mlx;
	char		*l_free;
	char		**map;
	int			max_y;
	int			max_x;
	int			box_size;
	int			key_val;
}		t_main;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// error.c
int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);

// free.c
int		mlx_free_kill_all(t_main *main);

// init_cub3d.c
int		init_cub3d(t_main *main);

// actions_key.c
int		is_wall(double x, double y, t_main *main);
int		update_player(t_main *main);
int		actions_key_press(int keycode, t_main *main);
int		actions_key_release(int keycode, t_main *main);

// actions_mouse.c
int		actions_mouse(int button, int x, int y, t_main *main);

// draw_minimap.c
void	draw_minimap_test(t_main *main);
void	draw_player_test(t_main *main);
void	draw_player_destination(t_main *main);
void	draw_ray(t_main *main, double angle);
void	draw_minimap(t_main *main);

// draw_render.c
void	draw_floor(t_main *main, int x, int y);
void	draw_ceil(t_main *main, int x, int y);
int		draw_render(t_main *main);

// init_all.c
int		init_window(t_main *main);
int		init_cub3d(t_main *main);
int		init_all(t_main *main);


// main.c
int		where_is_my_hero(int *x, int *y, t_main *main);
int		argv_check(int argc, char *map, t_main *main);
int		main(int argc, char **argv);

// map_borders_func.c
int		map_borders_inside(t_main *main);
int		map_borders_left(t_main *main);
int		map_borders_bottom(t_main *main);
int		map_borders_right(t_main *main);
int		map_borders_top(t_main *main);

// map_definitions_check.c
int		map_definitions_check_rgb(t_main *main);
int		xpm_file_check(char *str, char *name);
int		map_definitions_check(int count, char *line, int limit, t_main *main);

// map_definitions_rgb.c
int		map_definitions_rgb_c(t_main *main);
int		map_definitions_rgb_f(t_main *main);
int		map_definitions_rgb(t_main *main);

// map_definitions.c
void	free_definitions(t_main *main);
int		map_definitions_invalid_input(char *line, int limit, t_main *main);
char	*map_read_definitions(char *line, int *limit, int *count, int size);
void	map_definitions_init(t_main *main);
int		map_definitions(char *line, t_main *main);

// map_map.c
int		map_borders(t_main *main);
int		map_max_lenght(char *line, char c);
int		map_find_borders(char *line, int start, int *map_end);
int		map_skip_empty_line(char *line, int limit);
int		map_map(char *line, int start, t_main *main);

// map.c
char	*map_read(int fd);
int		map_check(int fd, t_main *main);

// player.c
void	player_turn(t_main *main, int way, double val);
void	player_move(t_main *main, int way, double val);

// set_mlx.c
void	put_pixe( t_main *main, double x, int y, double color);
int		window_set(t_main *main);

// utils_func.c
void	free_pstr(char **line);
int		err(char *err_output);
char	*ft_chrjoin(char *s1, char c);
int		ft_strncmp_edited(const char *s1, const char *s2, size_t n);
int		ft_strcmp_edited(char *s1, char *s2);

// utils_map_split.c
char	*map_split_stringfind(const char *s, char c, int max);
size_t	map_split_wordcount(char *s, char c);
char	**map_split(char *line, char c, int max);

#endif

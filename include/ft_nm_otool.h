/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:18:50 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/15 10:49:40 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

# define DEFAULT_FILE "a.out"

# include <stdint.h>
# include <stddef.h>

# define N_FUNC_PTR 5
# define FUNC_AR 0
# define FUNC_FAT_64 1
# define FUNC_FAT_32 2
# define FUNC_OBJ_64 3
# define FUNC_OBJ_32 4

enum			e_command
{
	NM, OTOOL
};

typedef struct	s_cpu
{
	char			*cpuname;
	uint32_t		cputype;
}				t_cpu;

typedef struct	s_nm_otool
{
	enum e_command	command;
	void			*env;
	void			*end_of_file;
	void			(*func_ptr[N_FUNC_PTR])\
					(struct s_nm_otool *, void*, const char*, uint8_t);
}				t_nm_otool;

int				is_ptr_in_file(const void *end_of_file, const void *ptr);

int				open_and_map(const char *filename,\
					void **ptr, size_t *size, enum e_command command);
void			close_and_unmap(void *ptr, size_t size, int fd);
int				handle_file(t_nm_otool *nm_otool, const char *filename,
					int print_filename);
int				handle_file_objects(t_nm_otool *nm_otool,\
					void *ptr, const char *filename);

const char		*get_cpuname(uint32_t cputype);
void			ar(t_nm_otool *nm_otool,\
					void *ptr, const char *filename, uint8_t swap);
void			fat_32(t_nm_otool *nm_otool,\
					void *ptr, const char *filename, uint8_t swap);
void			fat_64(t_nm_otool *nm_otool,\
					void *ptr, const char *filename, uint8_t swap);

#endif

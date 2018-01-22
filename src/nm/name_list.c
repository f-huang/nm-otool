/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 13:02:35 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/22 17:50:43 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <mach-o/fat.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ar.h>
#include "libft.h"
#include "ft_nm.h"

static int	handle_filetype(t_nm *nm, void *ptr, const char *file)
{
	uint32_t	magic_number;
	// int			swap;

	magic_number = *((int*)ptr);
	// swap = (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM || magic_number == FAT_CIGAM);
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64_bits(nm, ptr);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		handle_32_bits(nm, ptr);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		ft_putendl("fat");
	}
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
	{
		ft_putendl("fat64");
	}
	else if (ft_strnequ(((struct ar_hdr*)ptr)->ar_name, ARMAG, SARMAG))
	{
		handle_ar(nm, ptr, file);
	}
	else
	{
		ft_printf_fd(2, PROGRAM_NAME": %s: The file was not recognized as a valid object file.\n", file);
		return (0);
	}
	return (1);
}

static void	handle_error(const char *file, struct stat buf, const int fd, const void *ptr)
{
	int		ret;

	if (fd == -1)
	{
		ret = fstat(fd, &buf);
		if (ret < 0)
			ft_printf_fd(2, PROGRAM_NAME": %s: Could not open file.\n", file);
		else if (S_ISDIR(buf.st_mode) == 1)
			ft_printf_fd(2, PROGRAM_NAME": %s: Is a directory.\n", file);
		else if (buf.st_size == 0)
			ft_printf_fd(2, PROGRAM_NAME": %s: Is an empty file.\n", file);
	}
	else if (ptr == NULL)
		ft_printf_fd(2, PROGRAM_NAME": %s: Could not be mapped.\n", file);
}

int			name_list(t_nm *nm)
{
	int			i;
	int			fd;
	struct stat	buf;
	void		*ptr;

	i = -1;
	ptr = NULL;
	while (nm->files[++i])
	{
		ft_bzero(&buf, sizeof(struct stat));
		if ((fd = open(nm->files[i], O_RDONLY)) < 0 || fstat(fd, &buf) < 0\
			|| (ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			handle_error(nm->files[i], buf, fd, ptr);
		else
		{
			if (ft_tablen(nm->files) > 1)
				ft_printf("\n%s:\n", nm->files[i]);
			handle_filetype(nm, ptr, nm->files[i]);
			print_symbol_table(nm->symbols, nm->format, nm->options);
			if (ptr)
				munmap(ptr, buf.st_size);
			if (fd != -1)
				close(fd);
			ft_bzero(nm->sections, N_SECTION * sizeof(t_section));
			nm->section_ordinal = 0;
			symbol_clear(&nm->symbols);
		}
	}
	return (1);
}

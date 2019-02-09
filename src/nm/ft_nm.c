/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 13:02:35 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/01 11:42:49 by fhuang           ###   ########.fr       */
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

int	ft_nm(t_nm *nm, void *ptr, size_t file_size, const char *filename)
{
	uint32_t	magic;
	uint8_t		swap;

	if (file_size)
		nm->end_of_file = ptr + file_size;
	magic = *((int*)ptr);
	swap = (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM || magic == FAT_CIGAM_64);
	// ft_printf("swap: %i\n", swap);
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	{
		nm_64_bits(nm, ptr, swap);
	}
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
	{
		// ft_putendl("32b");
		nm_32_bits(nm, ptr, swap);
	}
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
	{
		// ft_putendl("fat32");
		nm_fat_32(nm, ptr, filename, swap);
	}
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
	{
		// ft_putendl("fat64");
		nm_fat_64(nm, ptr, filename, swap);
	}
	else if (ft_strnequ(((struct ar_hdr*)ptr)->ar_name, ARMAG, SARMAG))
	{
		// ft_putendl("ar");
		nm_ar(nm, ptr, filename);
	}
	else
	{
		ft_printf_fd(2, PROGRAM_NAME\
			": %s: The file was not recognized as a valid object file.\n",\
			filename);
		return (0);
	}
	return (1);
}

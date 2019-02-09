/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/05 14:56:07 by fhuang           ###   ########.fr       */
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
#include "ft_otool.h"

int	ft_otool(t_otool *otool, void *ptr, size_t file_size, const char *filename)
{
	uint32_t	magic;
	uint8_t		swap;

	magic = *((int*)ptr);
	swap = (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM || magic == FAT_CIGAM_64);
	(void)file_size;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		otool_64_bits(otool, ptr, filename);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		otool_32_bits(otool, ptr, filename);
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		otool_fat(otool, ptr);
	else if (ft_strnequ(((struct ar_hdr*)ptr)->ar_name, ARMAG, SARMAG))
		otool_ar(otool, ptr, filename);
	else
	{
		ft_printf_fd(2,\
			PROGRAM_NAME\
			": %s: The file was not recognized as a valid object file.\n",\
			filename);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:48:35 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/26 18:10:00 by fhuang           ###   ########.fr       */
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

int	ft_otool(t_otool *otool, void *ptr, const char *filename)
{
	uint32_t	magic_number;

	magic_number = *((int*)ptr);
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		otool_64_bits(otool, ptr, filename);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		otool_32_bits(otool, ptr, filename);
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
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

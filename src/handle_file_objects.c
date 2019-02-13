/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_objects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:48:10 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 16:14:53 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <ar.h>
#include "libft.h"
#include "ft_nm_otool.h"
#include "ft_nm.h"

int	handle_file_objects(t_nm_otool *nm_otool, void *ptr, const char *filename)
{
	uint32_t	magic;
	uint8_t		swap;

	magic = *((int*)ptr);
	swap = (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM || magic == FAT_CIGAM_64);
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64) {
		// ft_putendl("obj 64");
		nm_otool->func_ptr[FUNC_OBJ_64](nm_otool, ptr, filename, swap);
	}
	else if (magic == MH_MAGIC || magic == MH_CIGAM) {
		// ft_putendl("obj 32");
		nm_otool->func_ptr[FUNC_OBJ_32](nm_otool, ptr, filename, swap);
	}
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM) {
		// ft_putendl("fat 32");
		nm_otool->func_ptr[FUNC_FAT_32](nm_otool, ptr, filename, swap);
	}
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64) {
		// ft_putendl("fat 64");
		nm_otool->func_ptr[FUNC_FAT_64](nm_otool, ptr, filename, swap);
	}
	else if (ft_strnequ(((struct ar_hdr*)ptr)->ar_name, ARMAG, SARMAG)) {
		// ft_psutendl("ar");
		nm_otool->func_ptr[FUNC_AR](nm_otool, ptr, filename, swap);
	}
	else
	{
		ft_printf_fd(2, "%s: %s: The file was not recognized as a valid object file.\n",\
			nm_otool->command == NM ? "nm" : "otool", filename);
		return (0);
	}
	return (1);
}

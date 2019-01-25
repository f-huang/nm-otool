/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 13:02:35 by fhuang            #+#    #+#             */
/*   Updated: 2019/01/25 15:56:38 by fhuang           ###   ########.fr       */
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

int	ft_nm(t_nm *nm, void *ptr, const char *filename)
{
	uint32_t	magic_number;

	magic_number = *((int*)ptr);
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		nm_64_bits(nm, ptr);
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		nm_32_bits(nm, ptr);
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
		nm_fat(nm, ptr);
	else if (ft_strnequ(((struct ar_hdr*)ptr)->ar_name, ARMAG, SARMAG))
		nm_ar(nm, ptr, filename);
	else
	{
		ft_printf_fd(2, PROGRAM_NAME\
			": %s: The file was not recognized as a valid object file.\n",\
			filename);
		return (0);
	}
	return (1);
}

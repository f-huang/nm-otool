/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 19:07:04 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/12 14:30:06 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include "ft_nm_otool.h"
#include "ft_swap.h"
#include "ft_otool.h"
#include "libft.h"

static int64_t	got_my_host(struct fat_arch_64 *fat, uint64_t nfat_arch, uint8_t swap)
{
	uint64_t			i;

	i = 0;
	while (i < nfat_arch)
	{
		if (swap_64(fat[i].cputype, swap) == CPU_TYPE_X86_64)
			return (i);
		++i;
	}
	return (-1);
}

static void	output(const char *filename, uint64_t nfat_arch, uint64_t cputype)
{
	static const char	*format_filename = "%s:\n";
	static const char	*format_filename_cputype = "%s (architecture %s):\n";

	if (nfat_arch == 1)
		ft_printf(format_filename, filename);
	else
		ft_printf(format_filename_cputype, filename, get_cpuname(cputype));
}

static void	parse_object(t_otool *otool, struct fat_header *header, uint64_t offset, const char *filename)
{
	void				*ptr;

	ptr = header;
	ptr += offset;
	ft_otool(otool, ptr, 0, filename);
}


void	otool_fat_64(t_otool *otool, void *ptr, const char *filename, uint8_t swap)
{
	struct fat_header	*header;
	struct fat_arch_64		*fat;
	int64_t				i;
	uint64_t			nfat_arch;

	header = (struct fat_header*)ptr;
	fat = (struct fat_arch_64*)(ptr + sizeof(struct fat_header));
	nfat_arch = swap_64(header->nfat_arch, swap);
	if ((i = got_my_host(fat, nfat_arch, swap)) != -1)
		parse_object(otool, header, swap_64(fat[i].offset, swap), filename);
	else
		while ((uint64_t)++i < nfat_arch)
		{
			output(filename, nfat_arch, swap_64(fat[i].cputype, swap));
			parse_object(otool, header, swap_64(fat[i].offset, swap), filename);
		}
}

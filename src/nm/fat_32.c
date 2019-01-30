/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 19:07:04 by fhuang            #+#    #+#             */
/*   Updated: 2019/01/30 15:35:44 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach/machine.h>
#include "ft_nm.h"
#include "libft.h"

static int32_t	got_my_host(struct fat_arch *fat, uint32_t nfat_arch, uint8_t swap)
{
	uint32_t			i;

	i = 0;
	while (i < nfat_arch)
	{
		if (swap_32(fat[i].cputype, swap) == CPU_TYPE_X86_64)
			return (i);
		++i;
	}
	return (-1);
}

static const char*	get_cpuname(uint32_t cputype)
{
	static const t_cpu		cpus[] = {
		{"vax", CPU_TYPE_VAX},
		{"x86_64", CPU_TYPE_X86_64},
		{"i386", CPU_TYPE_X86},
		{"i386", CPU_TYPE_I386},
		{"i860", CPU_TYPE_I860},
		{"mc680x0", CPU_TYPE_MC680x0},
		{"mc88000", CPU_TYPE_MC88000},
		{"mc98000", CPU_TYPE_MC98000},
		{"hppa", CPU_TYPE_HPPA},
		{"arm", CPU_TYPE_ARM},
		{"arm64", CPU_TYPE_ARM64},
		{"sparc", CPU_TYPE_SPARC},
		{"ppc", CPU_TYPE_POWERPC},
		{"pcc64", CPU_TYPE_POWERPC64},
		{NULL, 0}
	};
	uint8_t				i;

	i = 0;
	while (cpus[i].cpuname)
	{
		if (cpus[i].cputype == cputype)
			return (cpus[i].cpuname);
		++i;
	}
	return ("");
}

static void	output(const char *filename, uint32_t nfat_arch, uint32_t cputype)
{
	static const char	*format_filename = "%s:\n";
	static const char	*format_filename_cputype = "\n%s (for architecture %s):\n";

	if (nfat_arch == 1)
		ft_printf(format_filename, filename);
	else
		ft_printf(format_filename_cputype, filename, get_cpuname(cputype));
}

static void	parse_object(t_nm *nm, struct fat_header *header, uint32_t offset, const char *filename)
{
	void				*ptr;

	ptr = header;
	ptr += offset;
	ft_nm(nm, ptr, filename);
}


void	nm_fat_32(t_nm *nm, void *ptr, const char *filename, uint8_t swap)
{
	struct fat_header	*header;
	struct fat_arch		*fat;
	int64_t				i;
	uint32_t			nfat_arch;

	header = (struct fat_header*)ptr;
	fat = (struct fat_arch*)(ptr + sizeof(struct fat_header));
	nfat_arch = swap_32(header->nfat_arch, swap);
	if ((i = got_my_host(fat, nfat_arch, swap)) != -1)
		parse_object(nm, header, swap_32(fat[i].offset, swap), filename);
	else
		while (++i < nfat_arch)
		{
			output(filename, nfat_arch, swap_32(fat[i].cputype, swap));
			parse_object(nm, header, swap_32(fat[i].offset, swap), filename);
		}
}

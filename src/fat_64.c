/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 19:07:04 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 20:09:00 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach/machine.h>
#include "ft_nm_otool.h"
#include "ft_swap.h"
#include "libft.h"

static int64_t	got_my_host(struct fat_arch_64 *fat,
							uint64_t nfat_arch,
							uint8_t swap)
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

static void		output(const char *filename,
					uint64_t nfat_arch,
					uint64_t cputype,
					enum e_command command)
{
	static const char	*format_filename = "%s:\n";
	static const char	*format_cputype_nm = "\n%s (for architecture %s):\n";
	static const char	*format_cputype_ot = "%s (architecture %s):\n";

	if (nfat_arch == 1)
		ft_printf(format_filename, filename);
	else
		ft_printf(command == NM ?\
			format_cputype_nm : format_cputype_ot,\
			filename, get_cpuname(cputype));
}

static void		parse_object(t_nm_otool *nm_otool,
						struct fat_header *header,
						uint64_t offset,
						const char *filename)
{
	void				*ptr;

	ptr = header;
	ptr += offset;
	if (is_ptr_in_file(nm_otool->end_of_file, ptr))
		handle_file_objects(nm_otool, ptr, filename);
}

void			fat_64(t_nm_otool *nm_otool,
						void *ptr,
						const char *filename,
						uint8_t swap)
{
	struct fat_header	*header;
	struct fat_arch_64	*fat;
	int64_t				i;
	int64_t				nfat_arch;

	header = (struct fat_header*)ptr;
	fat = (struct fat_arch_64*)(ptr + sizeof(struct fat_header));
	nfat_arch = swap_64(header->nfat_arch, swap);
	i = got_my_host(fat, nfat_arch, swap);
	if (!is_ptr_in_file(nm_otool->end_of_file, fat + i))
		return ;
	if (i != -1)
		parse_object(nm_otool, header, swap_64(fat[i].offset, swap), filename);
	else
		while (++i < nfat_arch
			&& is_ptr_in_file(nm_otool->end_of_file, fat + i))
		{
			output(filename, nfat_arch,
					swap_64(fat[i].cputype, swap),
					nm_otool->command);
			parse_object(nm_otool,
						header,
						swap_64(fat[i].offset, swap),
						filename);
		}
}

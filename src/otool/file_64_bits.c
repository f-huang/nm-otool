/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_64_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 18:57:24 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include "ft_swap.h"
#include "libft.h"
#include "ft_otool.h"

static void	print_section(struct section_64 *section,
							const void *ptr,
							void *end_of_file,
							uint8_t swap)
{
	uint64_t	size;
	uint64_t	i;
	uint64_t	j;
	uint8_t		*tmp;

	tmp = (uint8_t*)(ptr + swap_64(section->offset, swap));
	i = 0;
	size = swap_64(section->size, swap);
	if (!is_ptr_in_file(end_of_file, ptr + size)\
	|| !is_ptr_in_file(end_of_file, tmp + size))
		return ;
	while (i < size)
	{
		ft_printf("%0.16llx\t", swap_64(section->addr + i, swap));
		j = -1;
		while (!swap && ++j < 16 && i + j < size)
			ft_printf("%02x ", tmp[i + j]);
		while (swap && ++j < 16 && i + j < size)
			ft_printf("%02x%s", tmp[i + j], (j + 1) % 4 == 0 ? " " : "");
		ft_putchar('\n');
		i += 16;
	}
}

static void	parse_sections_64(t_nm_otool *nm_otool,
								struct segment_command_64 *segment,
								const void *ptr,
								uint8_t swap)
{
	uint64_t			i;
	struct section_64	*section;

	i = 0;
	section = (struct section_64*)(segment + 1);
	while (is_ptr_in_file(nm_otool->end_of_file, section + i)\
		&& i < swap_64(segment->nsects, swap))
	{
		if (ft_strequ(section[i].segname, SEG_TEXT)
			&& ft_strequ(section[i].sectname, SECT_TEXT))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			print_section(section + i, ptr, nm_otool->end_of_file, swap);
		}
		section = (struct section_64*)((void*)section +\
			sizeof(struct section_64));
		i++;
	}
}

void		otool_64_bits(t_nm_otool *nm_otool,
							void *ptr,
							const char *filename,
							uint8_t swap)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint64_t				i;

	header = (struct mach_header_64*)ptr;
	lc = ptr + sizeof(struct mach_header_64);
	i = 0;
	if (filename)
		ft_printf("%s:\n", filename);
	while (is_ptr_in_file(nm_otool->end_of_file, lc)\
		&& i < swap_64(header->ncmds, swap))
	{
		if (swap_64(lc->cmd, swap) == LC_SEGMENT_64)
			parse_sections_64(nm_otool,\
							(struct segment_command_64*)lc,\
							ptr,\
							swap);
		lc = (void*)lc + swap_64(lc->cmdsize, swap);
		++i;
	}
}

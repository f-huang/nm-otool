/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_bits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2018/02/20 12:25:47 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include "libft.h"
#include "ft_otool.h"
//
// #define SYMBOL_TYPE (nlist.n_type & N_TYPE)

static int	print_section(struct section_64 *section, const char *filename)
{
	uint64_t	i;
	uint64_t	j;
	uint64_t	addr;
	uint64_t	off;

	i = 0;
	addr = section->addr;
	off = section->offset;
	while (i < section->size)
	{
		j = 0;
		ft_printf("%0.16llx\t", addr);
		// while (j < 16 && i + j < section->size)
		// {
		// 	ft_printf("%.2hhx ", *(filename + off));
		// 	off++;
		// 	j++;
		// }
		j += 16;
		ft_printf("\n");
		i += j;
		addr += j;
	}
	(void)filename;
	return (1);
}

static int	lc_seg_64(struct segment_command_64 *sc, const char *filename)
{
	uint64_t			i;
	struct section_64	*section;

	i = 0;
	section = (struct section_64*)(sc + 1);
	while (i < sc->nsects)
	{
		if (ft_strequ(section[i].segname, SEG_TEXT)
			&& ft_strequ(section[i].sectname, SECT_TEXT))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			print_section(section + i, filename);
		}
		i++;
	}
	return (1);
}

int			otool_64_bits(t_otool *otool, void *ptr, const char *filename)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint64_t				i;

	header = (struct mach_header_64*)ptr;
	lc = ptr + sizeof(struct mach_header_64);
	i = 0;
	ft_printf("%s:\n", filename);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			lc_seg_64((struct segment_command_64*)lc, filename);
		lc = (void*)lc + lc->cmdsize;
		++i;
	}
	(void)otool;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_64_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2019/01/26 17:15:43 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include "ft_nm.h"
#include "libft.h"

#define SYMBOL_TYPE (n_type & N_TYPE)

static char	get_symbol_type(t_section *sections, struct nlist_64 nlist, uint8_t swap)
{
	char					ret;
	uint8_t					n_type;

	n_type = swap_32(nlist.n_type, swap);
	if (n_type & N_STAB)
		ret = '-';
	else if (SYMBOL_TYPE == N_ABS)
		ret = 'A';
	else if (SYMBOL_TYPE == N_INDR)
		ret = 'I';
	else if (SYMBOL_TYPE == N_UNDF && n_type & N_EXT && swap_64(nlist.n_value, swap))
		ret = 'C';
	else if (SYMBOL_TYPE == N_UNDF || SYMBOL_TYPE == N_PBUD)
		ret = 'U';
	else if (swap_64(nlist.n_desc, swap) & N_WEAK_REF)
		ret = 'W';
	else if (SYMBOL_TYPE == N_SECT)
	{
		if (!(ret = section_get_type(sections, swap_16(nlist.n_sect, swap))))
			ret = 'S';
	}
	else
		ret = '?';
	if (n_type & N_PEXT || !(n_type & N_EXT))
		ret = ft_tolower(ret);
	return (ret);
}

static void	get_symbols(t_nm *nm, struct symtab_command *sym, void *ptr, uint8_t swap)
{
	t_symbol				*new;
	int64_t					j;
	char					type;
	char					*stringtable;
	struct nlist_64			*nlist;

	nlist = (void*)ptr + swap_32(sym->symoff, swap);
	stringtable = (void*)ptr + swap_32(sym->stroff, swap);
	j = swap_32(sym->nsyms, swap) - 1;
	while (j >= 0)
	{
		type = get_symbol_type(nm->sections, nlist[j], swap);
		if (!is_symbol_skipped(nm->options, type) &&\
			(new = (t_symbol*)ft_memalloc(sizeof(t_symbol))))
		{
			new->type = type;
			new->value = swap_64(nlist[j].n_value, swap);
			new->name = ft_strdup(stringtable + swap_32(nlist[j].n_un.n_strx, swap));
			if (!new->name)
				ft_memdel((void**)&new);
			symbol_add(&nm->symbols, new, get_cmp_function(nm->options));
		}
		--j;
	}
}

void		nm_64_bits(t_nm *nm, void *ptr, uint8_t swap)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	uint64_t				i;

	header = (struct mach_header_64*)ptr;
	sym = NULL;
	lc = ptr + sizeof(struct mach_header_64);
	i = -1;
	while (++i < swap_64(header->ncmds, swap))
	{
		if (swap_64(lc->cmd, swap) == LC_SYMTAB)
			sym = (struct symtab_command *)lc;
		else if (swap_64(lc->cmd, swap) == LC_SEGMENT_64)
			section_add_64(nm->sections, &nm->section_ordinal,\
				(struct segment_command_64 *)lc, swap);
		lc = (void*)lc + swap_64(lc->cmdsize, swap);
	}
	get_symbols(nm, sym, ptr, swap);
	print_symbol_table(nm->symbols, nm->format, nm->options);
	ft_bzero(nm->sections, (N_SECTION * sizeof(t_section)));
	nm->section_ordinal = 0;
	symbol_clear(&nm->symbols);
}

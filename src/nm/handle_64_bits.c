/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_bits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/28 17:39:04 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include "libft.h"
#include "ft_nm.h"

#define SYMBOL_TYPE (nlist.n_type & N_TYPE)

static char	get_symbol_type(t_section *sections, struct nlist_64 nlist)
{
	char	ret;

	if (nlist.n_type & N_STAB)
		ret = '-';
	else if (SYMBOL_TYPE == N_ABS)
		ret = 'A';
	else if (SYMBOL_TYPE == N_INDR)
		ret = 'I';
	else if (SYMBOL_TYPE == N_UNDF && nlist.n_type & N_EXT && nlist.n_value)
		ret = 'C';
	else if (SYMBOL_TYPE == N_UNDF || SYMBOL_TYPE == N_PBUD)
		ret = 'U';
	else if (SYMBOL_TYPE == N_SECT)
	{
		if (!(ret = section_get_type(sections, nlist.n_sect)))
			ret = 'S';
	}
	else
		ret = 'S';
	if (nlist.n_type & N_PEXT || !(nlist.n_type & N_EXT))
		ret = ft_tolower(ret);
	return (ret);
}

static void	get_symbols(t_nm *nm, struct symtab_command *sym, void *ptr)
{
	t_symbol				*new;
	int32_t					j;
	char					type;
	char					*stringtable;
	struct nlist_64			*nlist;

	nlist = (void*)ptr + sym->symoff;
	stringtable = (void*)ptr + sym->stroff;
	j = sym->nsyms - 1;
	while (j >= 0)
	{
		type = get_symbol_type(nm->sections, nlist[j]);
		if (!is_symbol_skipped(nm->options, type) &&\
			(new = (t_symbol*)ft_memalloc(sizeof(t_symbol))))
		{
			new->type = type;
			new->value = nlist[j].n_value;
			new->name = ft_strdup(stringtable + nlist[j].n_un.n_strx);
			if (!new->name)
				ft_memdel((void**)&new);
			symbol_add(&nm->symbols, new, get_cmp_function(nm->options));
		}
		--j;
	}
}

void		handle_64_bits(t_nm *nm, void *ptr)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	uint32_t				i;

	header = (struct mach_header_64*)ptr;
	sym = NULL;
	lc = ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			sym = (struct symtab_command *)lc;
		else if (lc->cmd == LC_SEGMENT_64)
		{
			section_add_64(nm->sections, &nm->section_ordinal,\
				(struct segment_command_64 *)lc);
		}
		lc = (void*)lc + lc->cmdsize;
		++i;
	}
	get_symbols(nm, sym, ptr);
	print_symbol_table(nm->symbols, nm->format, nm->options);
	ft_bzero(nm->sections, N_SECTION * sizeof(t_section));
	nm->section_ordinal = 0;
	symbol_clear(&nm->symbols);
}

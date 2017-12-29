/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_bits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/29 19:27:42 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include "libft.h"
#include "ft_nm.h"

#define SYMBOL_TYPE (type & N_TYPE)
#define SYMBOL_SCOPE (type & N_EXT)

static char	get_symbol_type(uint8_t type, uint8_t n_sect)
{
	if (SYMBOL_TYPE == N_UNDF)
		return (SYMBOL_SCOPE ? 'U' : 'u');
	else if (SYMBOL_TYPE == N_ABS)
		return (SYMBOL_SCOPE ? 'A' : 'a');
	else if (SYMBOL_TYPE == N_INDR)
		return (SYMBOL_SCOPE ? 'I' : 'i');
	else if (SYMBOL_TYPE == N_SECT)
		return (get_symbol_type(n_sect, 0));
	else
		return (SYMBOL_SCOPE ? 'S' : 's');
}

static void	get_symbols(struct symtab_command *sym, void *ptr)
{
	int32_t					j;
	char					*stringtable;
	struct nlist_64			*nlist;

	nlist = (void*)ptr + sym->symoff;
	stringtable = (void*)ptr + sym->stroff;
	j = sym->nsyms - 1;
	ft_printf("NO_SECT = %u\n", NO_SECT);
	while (j >= 0 && !ft_isstrempty(stringtable + nlist[j].n_un.n_strx))
	{
		// ft_printf("%lx\n", nlist[j].n_value);
		ft_printf("%u, %u, %u\t", nlist[j].n_type, nlist[j].n_sect, nlist[j].n_desc);
		ft_putchar(get_symbol_type(nlist[j].n_type, nlist[j].n_sect));
		ft_putchar('\t');
		ft_putendl(stringtable + nlist[j].n_un.n_strx);
		--j;
	}
}

void	handle_64_bits(t_nm *nm, void *ptr)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	uint32_t				i;
	uint32_t				ncmds;

	header = (struct mach_header_64*)ptr;
	// ft_printf("filetype: %p\n", header->filetype);
	ncmds = header->ncmds;
	lc = ptr + sizeof(*header);
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			ft_printf("nb symboles: %d\n", sym->nsyms);
			get_symbols(sym, ptr);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
		++i;
	}
	(void)nm;

}

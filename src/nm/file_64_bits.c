/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_64_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:34:40 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 19:58:39 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/nlist.h>
#include "ft_swap.h"
#include "ft_nm.h"
#include "libft.h"

static char	get_symbol_type(t_section *sections,
							struct nlist_64 nlist,
							uint8_t swap)
{
	char					ret;
	uint8_t					n_type;

	n_type = nlist.n_type;
	if (n_type & N_STAB)
		ret = '-';
	else if ((n_type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((n_type & N_TYPE) == N_INDR)
		ret = 'I';
	else if ((n_type & N_TYPE) == N_UNDF
		&& n_type & N_EXT && swap_64(nlist.n_value, swap))
		ret = 'C';
	else if ((n_type & N_TYPE) == N_UNDF || (n_type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((n_type & N_TYPE) == N_SECT)
	{
		if (!(ret = section_get_type(sections, nlist.n_sect)))
			ret = 'S';
	}
	else
		ret = '?';
	if (ret != '?' && !(n_type & N_EXT))
		ret = ft_tolower(ret);
	return (ret);
}

static void	push_new_symbol(t_nm_otool *nm_otool,
							const char *stringtable,
							struct nlist_64 *nlist,
							uint8_t swap)
{
	t_symbol				*new;
	char					type;

	type = get_symbol_type(((t_nm*)nm_otool->env)->sections, *nlist, swap);
	if (is_symbol_skipped(((t_nm*)nm_otool->env)->options, type))
		return ;
	if (!(new = (t_symbol*)ft_memalloc(sizeof(t_symbol))))
		return ;
	new->name = ft_strdup(stringtable + swap_32((*nlist).n_un.n_strx, swap));
	if (!new->name)
	{
		ft_memdel((void**)&new);
		return ;
	}
	new->type = type;
	new->value = swap_64((*nlist).n_value, swap);
	symbol_add(&((t_nm*)nm_otool->env)->symbols,
				new,
				get_cmp_function(((t_nm*)nm_otool->env)->options));
}

static void	get_symbols(t_nm_otool *nm_otool,
						struct symtab_command *sym,
						void *ptr,
						uint8_t swap)
{
	int64_t					j;
	char					*stringtable;
	struct nlist_64			*nlist;

	if (!sym || !ptr)
		return ;
	nlist = (void*)ptr + swap_32(sym->symoff, swap);
	stringtable = (void*)ptr + swap_32(sym->stroff, swap);
	j = swap_32(sym->nsyms, swap);
	while (--j >= 0)
	{
		if (!is_ptr_in_file(nm_otool->end_of_file, nlist + j)
		|| !is_ptr_in_file(nm_otool->end_of_file,
			stringtable + swap_32(nlist[j].n_un.n_strx, swap)))
			break ;
		push_new_symbol(nm_otool, stringtable, nlist + j, swap);
	}
}

static void	loop_through_commands(t_nm_otool *nm_otool,
									void *ptr,
									struct symtab_command **sym,
									uint8_t swap)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	uint64_t				i;

	header = (struct mach_header_64*)ptr;
	*sym = NULL;
	lc = ptr + sizeof(struct mach_header_64);
	i = -1;
	while (is_ptr_in_file(nm_otool->end_of_file, lc)
		&& ++i < swap_64(header->ncmds, swap))
	{
		if (swap_64(lc->cmd, swap) == LC_SYMTAB)
			*sym = (struct symtab_command *)lc;
		else if (swap_64(lc->cmd, swap) == LC_SEGMENT_64)
			section_add_64(((t_nm*)nm_otool->env)->sections,
							&((t_nm*)nm_otool->env)->section_ordinal,
							(struct segment_command_64 *)lc, swap);
		lc = (void*)lc + swap_64(lc->cmdsize, swap);
	}
}

void		nm_64_bits(t_nm_otool *nm_otool,
						void *ptr,
						const char *filename,
						uint8_t swap)
{
	struct symtab_command	*sym;

	loop_through_commands(nm_otool, ptr, &sym, swap);
	get_symbols(nm_otool, sym, ptr, swap);
	if (((t_nm*)nm_otool->env)->format < 0)
		((t_nm*)nm_otool->env)->format *= -1;
	print_symbol_table(((t_nm*)nm_otool->env)->symbols,
						((t_nm*)nm_otool->env)->format,
						((t_nm*)nm_otool->env)->options);
	ft_bzero(((t_nm*)nm_otool->env)->sections, N_SECTION * sizeof(t_section));
	((t_nm*)nm_otool->env)->section_ordinal = 0;
	symbol_clear(&((t_nm*)nm_otool->env)->symbols);
	(void)filename;
}

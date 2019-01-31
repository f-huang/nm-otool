/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:20:57 by fhuang            #+#    #+#             */
/*   Updated: 2019/01/31 11:22:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/ldsyms.h>
#include "libft.h"
#include "ft_nm.h"


static const char	*get_format_string(enum e_nm_format format,\
	int is_undefined, int is_32_bits)
{
	const struct s_nm_print	print[] = {
		{ HEXA, "%016lx %c %s\n", "% 16c %c %s\n" },
		{ DECIMAL, "%016ld %c %s\n", "% 16c %c %s\n" },
		{ OCTAL, "%016lo %c %s\n", "% 16c %c %s\n" },
		{ MH_NOT_32BITS, "%08lx %c %s\n", "% 8c %c %s\n" },
	};
	int						i;

	i = 0;
	if (is_32_bits)
		return (is_undefined ? print[3].str2 : print[3].str1);
	while (i < 3)
	{
		if (format == print[i].format)
			return (is_undefined ? print[i].str2 : print[i].str1);
		++i;
	}
	return (print[0].str1);
}

void				print_symbol_table(t_symbol *symbols,\
	enum e_nm_format format, int options, int is_32_bits)
{
	t_symbol				*iterator;

	iterator = symbols;
	while (iterator)
	{
		if (options & OPTION_U || options & OPTION_J)
			ft_putendl(iterator->name);
		else if (iterator->type != 'U' && iterator->type != 'u')
			ft_printf(get_format_string(format, 0, is_32_bits),\
				iterator->value,
				iterator->type,
				iterator->name);
		else
			ft_printf(get_format_string(format, 1, is_32_bits),\
				' ',
				iterator->type,
				iterator->name);
		iterator = iterator->next;
	}
}

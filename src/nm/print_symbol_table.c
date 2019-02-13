/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:20:57 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 17:52:29 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/ldsyms.h>
#include "libft.h"
#include "ft_nm.h"


static const char	*get_format_string(enum e_nm_format format,\
	int is_undefined)
{
	const struct s_nm_print	print[] = {
		{ HEXA_64, "%016lx %c %s\n", "% 16c %c %s\n" },
		{ DECIMAL_64, "%016ld %c %s\n", "% 16c %c %s\n" },
		{ OCTAL_64, "%016lo %c %s\n", "% 16c %c %s\n" },
		{ HEXA_32, "%08lx %c %s\n", "% 8c %c %s\n" },
		{ DECIMAL_32, "%08ld %c %s\n", "% 8c %c %s\n" },
		{ OCTAL_32, "%08lo %c %s\n", "% 8c %c %s\n" }
	};
	int						i;
	i = 0;
	while (i < 6)
	{
		if (format == print[i].format)
			return (is_undefined ? print[i].str2 : print[i].str1);
		++i;
	}
	return (print[0].str1);
}

void				print_symbol_table(t_symbol *symbols,\
	enum e_nm_format format, int options)
{
	t_symbol				*iterator;

	iterator = symbols;
	while (iterator)
	{
		if (options & OPTION_U || options & OPTION_J)
			ft_putendl(iterator->name);
		else if (iterator->type != 'U' && iterator->type != 'u')
			ft_printf(get_format_string(format, 0),\
				iterator->value,
				iterator->type,
				iterator->name);
		else
			ft_printf(get_format_string(format, 1),\
				' ',
				iterator->type,
				iterator->name);
		iterator = iterator->next;
	}
}

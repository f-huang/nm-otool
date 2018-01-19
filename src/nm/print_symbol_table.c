/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:20:57 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/19 13:59:29 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"


static const char	*get_format_string(enum e_nm_format format, int is_undefined)
{
	struct s_nm_print	print[] = {
		{ HEXA, "%016lx %c %s\n", "% 16c %c %s\n" },
		{ DECIMAL, "%016ld %c %s\n", "% 16c %c %s\n" },
		{ OCTAL, "%016lo %c %s\n", "% 16c %c %s\n" }
	};
	int					i;

	i = 0;
	while (i < 3)
	{
		if (format == print[i].format)
			return (is_undefined ? print[i].str2 : print[i].str1);
		++i;
	}
	return print[0].str1;
}

void	print_symbol_table(t_symbol *symbols, enum e_nm_format format, int options)
{

	t_symbol	*iterator;

	iterator = symbols;
	while (iterator)
	{
		if (options & OPTION_U || options & OPTION_J)
			ft_putendl(iterator->name);
		else if (iterator->type != 'U' && iterator->type != 'u')
			ft_printf(get_format_string(format, 0),\
				iterator->value,
				iterator->type,
				iterator->name
			);
		else
			ft_printf(get_format_string(format, 1),\
				' ',
				iterator->type,
				iterator->name
			);
		iterator = iterator->next;
	}
}

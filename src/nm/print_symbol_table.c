/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:20:57 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/18 17:10:18 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

void	print_symbol_table(t_symbol *symbols)
{
	t_symbol	*iterator;

	iterator = symbols;
	while (iterator)
	{
		if (iterator->type != 'U' && iterator->type != 'u')
			ft_printf("%016lx %c %s\n",\
				iterator->value,
				iterator->type,
				iterator->name
			);
		else
			ft_printf("% 16c %c %s\n",\
				' ',
				iterator->type,
				iterator->name
			);
		iterator = iterator->next;
	}
}
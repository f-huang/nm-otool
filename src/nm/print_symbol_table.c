/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:20:57 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/30 19:30:40 by fhuang           ###   ########.fr       */
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
			ft_printf("%015lx\t%c %s\n",\
				iterator->value,
				iterator->type,
				iterator->name
			);
		else
			ft_printf("% 14c\t%c %s\n",\
				' ',
				iterator->type,
				iterator->name
			);
		iterator = iterator->next;
	}
}

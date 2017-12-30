/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 19:05:49 by fhuang            #+#    #+#             */
/*   Updated: 2017/12/30 19:40:49 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

void	symbol_clear(t_symbol **symbols)
{
	t_symbol	*iterator;
	t_symbol	*tmp;

	tmp = NULL;
	iterator = *symbols;
	while (iterator)
	{
		tmp = iterator;
		iterator = iterator->next;
		ft_strdel(&tmp->name);
		ft_memdel((void**)&tmp);
	}
	*symbols = NULL;
}

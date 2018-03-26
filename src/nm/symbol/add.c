/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 18:58:23 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/26 18:32:58 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

void	symbol_add(t_symbol **symbols, t_symbol *new,\
	int (*cmp)(t_symbol, t_symbol))
{
	t_symbol	*iterator;
	t_symbol	*prev;

	if (!(prev = NULL) && !new)
		return ;
	iterator = *symbols;
	while (iterator)
	{
		if (cmp(*new, *iterator) <= 0)
			break ;
		prev = iterator;
		iterator = iterator->next;
	}
	if (iterator == *symbols)
	{
		new->next = *symbols;
		*symbols = new;
	}
	else if (prev && prev->next == NULL)
		prev->next = new;
	else
	{
		new->next = prev->next;
		prev->next = new;
	}
}

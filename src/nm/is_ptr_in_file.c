/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ptr_in_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 11:39:09 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/01 11:53:19 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_ptr_in_file(void *end_of_file, void* ptr)
{
	if (ptr > end_of_file)
	{
		ft_putendl_fd("File is corrupted.", 2);
		return (0);
	}
	return (1);
}

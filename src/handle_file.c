/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_through_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:18:24 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/26 17:56:44 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm_otool.h"

int		handle_file(void *env, const char *filename, int (*f)(void*, void *ptr, const char*))
{
	void	*ptr;
	size_t	size;
	int		fd;

	ptr = NULL;
	size = 0;
	if ((fd = open_and_map(filename, &ptr, &size)) != -1)
	{
		f(env, ptr, filename);
		close_and_unmap(ptr, size, fd);
	}
	return (0);
}

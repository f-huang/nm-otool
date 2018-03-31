/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:18:24 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/31 17:22:48 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm_otool.h"

int		handle_file(void *env, const char *filename,\
	int (*f)(void*, void *ptr, const char*))
{
	void	*ptr;
	size_t	size;
	int		fd;
	int		error;

	ptr = NULL;
	error = 0;
	size = 0;
	if ((fd = open_and_map(filename, &ptr, &size)) != -1)
	{
		error = f(env, ptr, filename) == 0 ? 1 : 0;
		close_and_unmap(ptr, size, fd);
	}
	else
		error = 1;
	return (error);
}

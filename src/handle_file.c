/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:18:24 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/13 20:32:05 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_nm_otool.h"
#include "libft.h"

int		handle_file(t_nm_otool *nm_otool,
					const char *filename,
					int print_filename)
{
	void	*ptr;
	size_t	size;
	int		fd;
	int		error;

	ptr = NULL;
	error = 0;
	size = 0;
	if ((fd = open_and_map(filename, &ptr, &size, nm_otool->command)) != -1)
	{
		if (print_filename)
			ft_printf("\n%s:\n", filename);
		nm_otool->end_of_file = ptr + size;
		error = handle_file_objects(nm_otool, ptr, filename) == 0 ? 1 : 0;
		close_and_unmap(ptr, size, fd);
	}
	else
		error = 1;
	return (error);
}

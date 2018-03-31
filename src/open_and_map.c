/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 13:07:30 by fhuang            #+#    #+#             */
/*   Updated: 2018/03/31 16:57:41 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include "ft_nm.h"

static void	handle_error(const char *file, int *fd, const void *ptr)
{
	struct stat	buf;
	int			ret;

	ret = fstat(*fd, &buf);
	if (ret < 0)
		ft_printf_fd(2, PROGRAM_NAME": %s: No such file or directory or "\
		"Could not open file.\n", file);
	else if (S_ISDIR(buf.st_mode) == 1)
		ft_printf_fd(2, PROGRAM_NAME": %s: Is a directory.\n", file);
	else if (buf.st_size == 0)
		ft_printf_fd(2, PROGRAM_NAME": %s: Is an empty file.\n", file);
	else if (ptr == NULL)
		ft_printf_fd(2, PROGRAM_NAME": %s: Could not be mapped.\n", file);
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

int			open_and_map(const char *filename, void **ptr, size_t *size)
{
	struct stat	buf;
	int			fd;

	if (!filename || !ptr)
		return (-1);
	ft_bzero(&buf, sizeof(struct stat));
	if ((fd = open(filename, O_RDONLY)) < 0\
		|| fstat(fd, &buf) < 0\
		|| S_ISDIR(buf.st_mode) == 1\
		|| (*ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))\
			== MAP_FAILED)
	{
		handle_error(filename, &fd, ptr);
	}
	*size = buf.st_size;
	return (fd);
}

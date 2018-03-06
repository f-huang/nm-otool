/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_unmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 13:12:14 by fhuang            #+#    #+#             */
/*   Updated: 2018/01/28 17:06:33 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>

void	close_and_unmap(void *ptr, size_t size, int fd)
{
	if (ptr && ptr != MAP_FAILED)
		munmap(ptr, size);
	if (fd != -1)
		close(fd);
}

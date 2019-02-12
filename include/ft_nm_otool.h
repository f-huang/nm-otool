/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:18:50 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/12 10:48:26 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

# define DEFAULT_FILE "a.out"

#include <stdint.h>
#include <stddef.h>

typedef struct		s_cpu
{
	char			*cpuname;
	uint32_t		cputype;
}					t_cpu;


int		open_and_map(const char *filename, void **ptr, size_t *size);
void	close_and_unmap(void *ptr, size_t size, int fd);
int		handle_file(void *env, const char *filename,\
			int (*f)(void*, void *, size_t, const char*));

const char*	get_cpuname(uint32_t cputype);

#endif

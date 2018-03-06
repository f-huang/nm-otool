/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 12:18:50 by fhuang            #+#    #+#             */
/*   Updated: 2018/02/20 12:19:13 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

// # include "ft_nm.h"
// # include "ft_otool.h"

# define DEFAULT_FILE "a.out"

int		open_and_map(const char *filename, void **ptr, size_t *size);
void	close_and_unmap(void *ptr, size_t size, int fd);
int		loop_through_arg(void *env, char **av, int i, int (*f)(void*, void *ptr, const char*));

#endif

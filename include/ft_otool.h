/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 08:40:36 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/01 11:31:42 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# define PROGRAM_NAME "otool"

/*
**	OPTIONS
**
**	-t     Display the contents of the (__TEXT,__text) section.
**	       With the -v flag, this disassembles the text.
**	       And with -V, it also symbolically disassembles the operands.
**	-d     Display the contents of the (__DATA,__data) section.
**	-o     Display the contents of the __OBJC segment\
**			used by the Objective-C run-time system.
**	-h     Display the Mach header.
**	-l     Display the load commands.
**	-v     Display verbosely (symbolically) when possible.
**	-V     Display  the disassembled operands symbolically\
**				(this implies the -v option).
*/

typedef struct	s_otool
{
	int			options;
}				t_otool;

int				ft_otool(t_otool *otool, void *ptr, size_t file_size, const char *filename);
void			otool_64_bits(t_otool *otool, void *ptr, const char *filename);
void			otool_32_bits(t_otool *otool, void *ptr, const char *filename);
void			otool_fat(t_otool *otool, void *ptr);
void			otool_ar(t_otool *otool, void *ptr, const char *filename);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cpuname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhuang <fhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:33:23 by fhuang            #+#    #+#             */
/*   Updated: 2019/02/12 10:48:36 by fhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <mach/machine.h>
#include "ft_nm_otool.h"

const char*	get_cpuname(uint32_t cputype)
{
	static const t_cpu		cpus[] = {
		{"vax", CPU_TYPE_VAX},
		{"x86_64", CPU_TYPE_X86_64},
		{"i386", CPU_TYPE_X86},
		{"i386", CPU_TYPE_I386},
		{"i860", CPU_TYPE_I860},
		{"mc680x0", CPU_TYPE_MC680x0},
		{"mc88000", CPU_TYPE_MC88000},
		{"mc98000", CPU_TYPE_MC98000},
		{"hppa", CPU_TYPE_HPPA},
		{"arm", CPU_TYPE_ARM},
		{"arm64", CPU_TYPE_ARM64},
		{"sparc", CPU_TYPE_SPARC},
		{"ppc", CPU_TYPE_POWERPC},
		{"pcc64", CPU_TYPE_POWERPC64},
		{NULL, 0}
	};
	uint8_t				i;

	i = 0;
	while (cpus[i].cpuname)
	{
		if (cpus[i].cputype == cputype)
			return (cpus[i].cpuname);
		++i;
	}
	return ("");
}

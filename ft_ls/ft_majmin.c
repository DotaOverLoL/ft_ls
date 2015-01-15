/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_majmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 16:30:27 by tlebrize          #+#    #+#             */
/*   Updated: 2015/01/08 16:37:44 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		ft_majmin(dev_t dev, t_width w)
{
	int		aspc;
	int		ispc;

	if (w.major > w.minor)
	{
		aspc = 1 + (w.major - ft_intlen(major(dev)));
		ispc = 1 + (w.major - ft_intlen(minor(dev)));
	}
	else
	{
		aspc = 1 + (w.minor - ft_intlen(major(dev)));
		ispc = 1 + (w.minor - ft_intlen(minor(dev)));
	}
	while (aspc-- != 0)
		ft_putchar(' ');
	ft_putnbr(major(dev));
	ft_putchar(',');
	while (ispc-- != 0)
		ft_putchar(' ');
	ft_putnbr(minor(dev));
}

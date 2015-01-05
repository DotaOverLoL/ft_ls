/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_majmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebrize <tlebrize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 16:30:27 by tlebrize          #+#    #+#             */
/*   Updated: 2014/12/30 16:46:01 by tlebrize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <kdev_t.h>

void		ft_majmin(dev_t)
{
	ft_putndr(MAJOR(dev));
	ft_putstr(", ");
	ft_putnbr(MINOR(dev));
}
